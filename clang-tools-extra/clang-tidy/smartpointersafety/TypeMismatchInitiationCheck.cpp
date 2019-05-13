//===--- TypeMismatchInitiationCheck.cpp - clang-tidy ---------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "TypeMismatchInitiationCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void TypeMismatchInitiationCheck::registerMatchers(MatchFinder *Finder) {
  auto newexpr = cxxNewExpr().bind("new");

  // Match ConstructExpr and method `reset` call with an argument of CXXNewExpr.
  Finder->addMatcher(
      stmt(anyOf(getSmartPointerConstructExprInTypeWithArgument(
                     getAutoPointerTypeConcreteMatcher(), newexpr),
                 getSmartPointerConstructExprInTypeWithArgument(
                     getSharedPointerTypeConcreteMatcher(), newexpr),
                 getSmartPointerConstructExprInTypeWithArgument(
                     getUniquePointerTypeConcreteMatcher(), newexpr),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getAutoPointerTypeConcreteMatcher(), newexpr),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getSharedPointerTypeConcreteMatcher(), newexpr),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getUniquePointerTypeConcreteMatcher(), newexpr))),
      this);
}

void TypeMismatchInitiationCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *newexpr = Result.Nodes.getNodeAs<CXXNewExpr>("new");
  const auto *ptrtype = Result.Nodes.getNodeAs<QualType>("PointerType");

  if (!newexpr || !ptrtype)
    return;

  // Check whether both types are array type at the same time.
  bool newIsArray = newexpr->isArray();
  bool ptrIsArray = (*ptrtype)->isArrayType();
  if (newIsArray != ptrIsArray) {
    diag(newexpr->getBeginLoc(),
         "Initiation CXXNewExpr type `" +
             newexpr->getConstructExpr()->getType().getAsString() +
             "' dose not match its declaration type `" +
             ptrtype->getAsString() + "'.");
  }
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

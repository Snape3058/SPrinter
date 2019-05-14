//===--- NonAllocatedMemoryInitiationCheck.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "NonAllocatedMemoryInitiationCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void NonAllocatedMemoryInitiationCheck::registerMatchers(MatchFinder *Finder) {
  auto getAddressOperator = unaryOperator(hasOperatorName("&")).bind("init");
  auto arrayPointer = expr(
      hasType(isAnyPointer()),
      hasDescendant(
          implicitCastExpr(hasCastKind(CK_ArrayToPointerDecay)).bind("init")));
  auto concreteAddress =
      cStyleCastExpr(hasCastKind(CK_IntegralToPointer)).bind("init");

  auto argument = anyOf(getAddressOperator, arrayPointer, concreteAddress);

  Finder->addMatcher(
      stmt(anyOf(getSmartPointerConstructExprInTypeWithArgument(
                     getAutoPointerTypeConcreteMatcher(), argument),
                 getSmartPointerConstructExprInTypeWithArgument(
                     getSharedPointerTypeConcreteMatcher(), argument),
                 getSmartPointerConstructExprInTypeWithArgument(
                     getUniquePointerTypeConcreteMatcher(), argument),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getAutoPointerTypeSimpleMatcher(), argument),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getSharedPointerTypeSimpleMatcher(), argument),
                 getSmartPointerMemberCallExprInTypeWithArgument(
                     "reset", getUniquePointerTypeSimpleMatcher(), argument))),
      this);
}

void NonAllocatedMemoryInitiationCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *init = Result.Nodes.getNodeAs<Expr>("init");

  if (!init)
    return;

  diag(init->getBeginLoc(),
       "Initiating smart pointer with non-allocated memory.");
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

//===--- DeallocatingObserverPointerCheck.cpp - clang-tidy ----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "DeallocatingObserverPointerCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void DeallocatingObserverPointerCheck::registerMatchers(MatchFinder *Finder) {
  auto callGet = expr(anyOf(getSmartPointerMemberCallExprInType(
                                "get", getAutoPointerTypeSimpleMatcher()),
                            getSmartPointerMemberCallExprInType(
                                "get", getSharedPointerTypeSimpleMatcher()),
                            getSmartPointerMemberCallExprInType(
                                "get", getUniquePointerTypeSimpleMatcher())))
                     .bind("get");

  auto refFromGet =
      declRefExpr(
          hasDeclaration(varDecl(hasType(isAnyPointer()),
                                 hasInitializer(ignoringImplicit(callGet)))))
          .bind("ref");

  Finder->addMatcher(
      cxxDeleteExpr(has(expr(ignoringImpCasts(anyOf(callGet, refFromGet)))))
          .bind("del"),
      this);
}

void DeallocatingObserverPointerCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *del = Result.Nodes.getNodeAs<CXXDeleteExpr>("del");
  const auto *get = Result.Nodes.getNodeAs<CXXMemberCallExpr>("get");

  if (!del || !get)
    return;

  diag(del->getArgument()->getBeginLoc(),
       "Deallocating pointer values returned from smart pointer observer.");

  if (Result.Nodes.getNodeAs<DeclRefExpr>("ref")) {
    diag(get->getBeginLoc(),
         "Referenced variable assigned here:", DiagnosticIDs::Note);
  }
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

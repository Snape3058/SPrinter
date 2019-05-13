//===--- UncheckedLockedWeakPointerCheck.cpp - clang-tidy -----------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UncheckedLockedWeakPointerCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void UncheckedLockedWeakPointerCheck::registerMatchers(MatchFinder *Finder) {
  auto callLock = cxxMemberCallExpr(
      callee(memberExpr(hasDeclaration(cxxMethodDecl(hasName("lock"))),
                        hasObjectExpression(ignoringImpCasts(declRefExpr(
                            hasType(getWeakPointerTypeSimpleMatcher())))))));

  auto refFromLock = declRefExpr(hasDeclaration(
      varDecl(
          hasType(getSharedPointerTypeSimpleMatcher()),
          hasInitializer(ignoringImplicit(cxxConstructExpr(
              argumentCountIs(1), hasArgument(0, ignoringImplicit(callLock))))))
          .bind("SharedPtrUse")));

  Finder->addMatcher(
      cxxOperatorCallExpr(
          anyOf(hasOverloadedOperatorName("->"),
                hasOverloadedOperatorName("*")),
          argumentCountIs(1),
          hasArgument(0, ignoringImplicit(anyOf(callLock, refFromLock))),
          unless(hasAncestor(ifStmt(
              hasCondition(hasDescendant(cxxMemberCallExpr(callee(memberExpr(
                  member(hasName("operator bool")),
                  hasObjectExpression(
                      ignoringImpCasts(declRefExpr(hasDeclaration(
                          varDecl(equalsBoundNode("SharedPtrUse")))))))))))))))
          .bind("access"),
      this);
}

void UncheckedLockedWeakPointerCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *access = Result.Nodes.getNodeAs<CXXOperatorCallExpr>("access");

  if (!access)
    return;

  diag(access->getOperatorLoc(),
       "Validity of locked weak_ptr is unchecked, may have been expired.");
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

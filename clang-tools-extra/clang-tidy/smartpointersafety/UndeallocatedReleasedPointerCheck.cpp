//===--- UndeallocatedReleasedPointerCheck.cpp - clang-tidy ---------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "UndeallocatedReleasedPointerCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void UndeallocatedReleasedPointerCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      expr(anyOf(getSmartPointerMemberCallExprInType(
                     "release", getAutoPointerTypeSimpleMatcher()),
                 getSmartPointerMemberCallExprInType(
                     "release", getUniquePointerTypeSimpleMatcher())),
           hasParent(stmt(anyOf(
               unaryOperator(hasOperatorName("*")), memberExpr(isArrow()),
               // GNU statement expressions should not be matched, as we do not
               // know whether this return value may be used outside
               compoundStmt(unless(hasParent(stmtExpr()))), ifStmt(),
               whileStmt(), doStmt(), forStmt(), cxxForRangeStmt(),
               switchStmt(), caseStmt(), defaultStmt(),
               // Used to match the conditional statement in if, for, and while.
               implicitCastExpr(hasCastKind(CK_PointerToBoolean))))))
          .bind("release"),
      this);
}

void UndeallocatedReleasedPointerCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *release = Result.Nodes.getNodeAs<CXXMemberCallExpr>("release");

  if (!release)
    return;

  diag(release->getBeginLoc(),
       "Undeallocated released pointer may cause memory leaked.");
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

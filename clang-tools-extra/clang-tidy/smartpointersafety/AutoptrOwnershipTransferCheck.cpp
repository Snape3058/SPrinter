//===--- AutoptrOwnershipTransferCheck.cpp - clang-tidy -------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AutoptrOwnershipTransferCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void AutoptrOwnershipTransferCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      cxxConstructExpr(hasDeclaration(cxxConstructorDecl(isCopyConstructor())),
                       hasType(getAutoPointerTypeSimpleMatcher()))
          .bind("trans"),
      this);
}

void AutoptrOwnershipTransferCheck::check(
    const MatchFinder::MatchResult &Result) {
  const auto *trans = Result.Nodes.getNodeAs<CXXConstructExpr>("trans");

  if (!trans)
    return;

  diag(trans->getLocation(), "Ownership transfer of `auto_ptr' happens here:");
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

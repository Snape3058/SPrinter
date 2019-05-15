//===--- PrivateAutoptrInClassCheck.cpp - clang-tidy ----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "PrivateAutoptrInClassCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void PrivateAutoptrInClassCheck::registerMatchers(MatchFinder *Finder) {
  // Match only classes with private auto_ptr field.
  // Leave checking of copy constructor and copy assignment to the checker.
  Finder->addMatcher(
      cxxRecordDecl(
          has(fieldDecl(hasType(getAutoPointerTypeSimpleMatcher()), isPrivate())
                  .bind("ptr")))
          .bind("decl"),
      this);
}

void PrivateAutoptrInClassCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *decl = Result.Nodes.getNodeAs<CXXRecordDecl>("decl");

  if (!decl)
    return;

  // check whether two methods are default.
  if (decl->hasUserDeclaredCopyConstructor() &&
      decl->hasUserDeclaredCopyAssignment())
    return;

  diag(Result.Nodes.getNodeAs<FieldDecl>("ptr")->getBeginLoc(),
       "Class declares a field of type `auto_ptr' with default copy "
       "constructor and/or copy assignment operator.");
  diag(decl->getBeginLoc(), "Class defined here:", DiagnosticIDs::Note);
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

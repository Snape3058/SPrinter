//===--- AutoptrInContainerCheck.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "AutoptrInContainerCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void AutoptrInContainerCheck::registerMatchers(MatchFinder *Finder) {
  Finder->addMatcher(
      varDecl(hasType(qualType(hasDeclaration(classTemplateSpecializationDecl(
                  hasAnyName({
#define NAME(name) "::std::" #name,
#include "STL-Containers.inc"
#undef NAME
                  }),
                  hasAnyTemplateArgument(templateArgument(
                      refersToType(getAutoPointerTypeSimpleMatcher()))))))))
          .bind("stl"),
      this);
}

void AutoptrInContainerCheck::check(const MatchFinder::MatchResult &Result) {
  const auto *stl = Result.Nodes.getNodeAs<VarDecl>("stl");

  if (!stl)
    return;

  diag(stl->getBeginLoc(), "Put `auto_ptr' in STL containers may cause "
                           "unexpected behaviour under some circumstances.");
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

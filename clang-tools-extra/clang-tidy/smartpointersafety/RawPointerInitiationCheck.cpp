//===--- RawPointerInitiationCheck.cpp - clang-tidy ---------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RawPointerInitiationCheck.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ExprCXX.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

using SmartPointerMatcherType =
    ast_matchers::internal::BindableMatcher<QualType>;
SmartPointerMatcherType getUniquePointerTypeMatcher() {
  return qualType(hasUnqualifiedDesugaredType(
      recordType(hasDeclaration(classTemplateSpecializationDecl(
          hasName("::std::unique_ptr"), templateArgumentCountIs(2),
          hasTemplateArgument(0, templateArgument(refersToType(
                                     qualType().bind("PointerType")))),
          hasTemplateArgument(
              1,
              templateArgument(refersToType(
                  qualType(hasDeclaration(classTemplateSpecializationDecl(
                      hasName("::std::default_delete"),
                      templateArgumentCountIs(1),
                      hasTemplateArgument(
                          0, templateArgument(refersToType(qualType(
                                 equalsBoundNode("PointerType"))))))))))))))));
}

void RawPointerInitiationCheck::registerMatchers(MatchFinder *Finder) {
  // FIXME: Add matchers.
  Finder->addMatcher(cxxConstructExpr(hasType(getUniquePointerTypeMatcher()),
                                      argumentCountIs(1),
                                      hasArgument(0, declRefExpr().bind("ptr")))
                         .bind("ctor"),
                     this);
  Finder->addMatcher(functionDecl(), this);
}

void RawPointerInitiationCheck::check(const MatchFinder::MatchResult &Result) {
  static std::map<const ValueDecl *, const CXXConstructExpr *> definitions;

  const auto *ctor = Result.Nodes.getNodeAs<CXXConstructExpr>("ctor");
  const auto *ptr = Result.Nodes.getNodeAs<DeclRefExpr>("ptr");
  if (!ptr) {
    // Trace FunctionDecl and clear the stored data of last function:
    definitions.clear();
    return;
  }

  const auto *decl = ptr->getDecl();

  if (definitions.end() == definitions.find(decl)) {
    definitions[decl] = ctor;
    diag(ptr->getLocation(), "Creating smart pointer with raw pointer.");
  } else {
    diag(
        ptr->getLocation(),
        "Creating smart pointer with the same raw pointer for more than once.");
    diag(definitions[decl]->getLocation(),
         "The first definition using this raw pointer: ", DiagnosticIDs::Note);
  }
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

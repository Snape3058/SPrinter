//===--- SmartPointerTypeMatcher.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "SmartPointerTypeMatcher.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

TypeMatcher getSmartPointerTypeConcreteMatcher(const char *name) {
  return qualType(hasUnqualifiedDesugaredType(
      recordType(hasDeclaration(classTemplateSpecializationDecl(
          hasName(name), templateArgumentCountIs(1),
          hasTemplateArgument(0, templateArgument(refersToType(
                                     qualType().bind("PointerType")))))))));
}

TypeMatcher getUniquePointerTypeConcreteMatcher(TypeMatcher deleter) {
  return qualType(hasUnqualifiedDesugaredType(
      recordType(hasDeclaration(classTemplateSpecializationDecl(
          hasName("::std::unique_ptr"), templateArgumentCountIs(2),
          hasTemplateArgument(0, templateArgument(refersToType(
                                     qualType().bind("PointerType")))),
          hasTemplateArgument(1, templateArgument(refersToType(deleter))))))));
}

TypeMatcher getUniquePointerDefaultDeleterTypeConcreteMatcher() {
  return qualType(hasDeclaration(classTemplateSpecializationDecl(
      hasName("::std::default_delete"), templateArgumentCountIs(1),
      hasTemplateArgument(0, templateArgument(refersToType(
                                 qualType(equalsBoundNode("PointerType"))))))));
}

StatementMatcher
getSmartPointerConstructExprInTypeWithArgument(TypeMatcher type,
                                               StatementMatcher argument) {
  return cxxConstructExpr(hasType(type), argumentCountIs(1),
                          hasArgument(0, ignoringImpCasts(argument)));
}

StatementMatcher getSmartPointerMemberCallExprInTypeWithArgument(
    const char *name, TypeMatcher type, StatementMatcher argument) {
  return cxxMemberCallExpr(
      callee(memberExpr(
          hasDeclaration(cxxMethodDecl(hasName(name))),
          hasObjectExpression(ignoringImpCasts(declRefExpr(hasType(type)))))),
      argumentCountIs(1), hasArgument(0, ignoringImpCasts(argument)));
}

StatementMatcher getSmartPointerMemberCallExprInType(const char *name,
                                                     TypeMatcher type) {
  return cxxMemberCallExpr(callee(memberExpr(
      hasDeclaration(cxxMethodDecl(hasName(name))),
      hasObjectExpression(ignoringImpCasts(declRefExpr(hasType(type)))))));
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

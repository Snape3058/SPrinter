//===--- SmartPointerTypeMatcher.h - clang-tidy ---------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SMARTPOINTERSAFETY_SMARTPOINTERTYPEMATCHER_H
#define LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SMARTPOINTERSAFETY_SMARTPOINTERTYPEMATCHER_H

#include "../ClangTidyCheck.h"

namespace clang {
namespace tidy {
namespace smartpointersafety {

constexpr const char *AutoPointerName = "::std::auto_ptr";
constexpr const char *SharedPointerName = "::std::shared_ptr";
constexpr const char *UniquePointerName = "::std::unique_ptr";
constexpr const char *WeakPointerName = "::std::weak_ptr";

/// Define matcher to match a QualType `template<typename T>name` with T bound
/// as "PointerType".
ast_matchers::TypeMatcher getSmartPointerTypeConcreteMatcher(const char *name);

/// Define matcher to match a QualType with its name.
inline ast_matchers::TypeMatcher
getSmartPointerTypeSimpleMatcher(const char *name) {
  using namespace clang::ast_matchers;
  return qualType(hasDeclaration(namedDecl(hasName(name))));
}

#define DEFINE_MATCHER_WITH_NAME_AND_KIND(NAME, KIND, NAMESTR)                 \
  inline ast_matchers::TypeMatcher get##NAME##PointerType##KIND##Matcher() {   \
    return getSmartPointerType##KIND##Matcher(NAMESTR);                        \
  }

DEFINE_MATCHER_WITH_NAME_AND_KIND(Auto, Concrete, AutoPointerName)
DEFINE_MATCHER_WITH_NAME_AND_KIND(Auto, Simple, AutoPointerName)
DEFINE_MATCHER_WITH_NAME_AND_KIND(Shared, Concrete, SharedPointerName)
DEFINE_MATCHER_WITH_NAME_AND_KIND(Shared, Simple, SharedPointerName)
DEFINE_MATCHER_WITH_NAME_AND_KIND(Weak, Concrete, WeakPointerName)
DEFINE_MATCHER_WITH_NAME_AND_KIND(Weak, Simple, WeakPointerName)

/// Define matcher to match the QualType
/// `template<typename T, typename D>std::unique_ptr` with T bound as
/// "PointerType", and D of parameter `deleter`.
ast_matchers::TypeMatcher
getUniquePointerTypeConcreteMatcher(ast_matchers::TypeMatcher deleter);

/// Define matcher to match the default_delete deleter of unique_ptr.
ast_matchers::TypeMatcher getUniquePointerDefaultDeleterTypeConcreteMatcher();

inline ast_matchers::TypeMatcher getUniquePointerTypeConcreteMatcher() {
  return getUniquePointerTypeConcreteMatcher(
      getUniquePointerDefaultDeleterTypeConcreteMatcher());
}

DEFINE_MATCHER_WITH_NAME_AND_KIND(Unique, Simple, UniquePointerName)

#undef DEFINE_MATCHER_WITH_NAME_AND_KIND

/// Define matcher to match the ConstructExpr of a smart pointer with the given
/// `type` and `argument`.
ast_matchers::StatementMatcher getSmartPointerConstructExprInTypeWithArgument(
    ast_matchers::TypeMatcher type, ast_matchers::StatementMatcher argument);

/// Define matcher to match the member function call with `name` of a smart
/// pointer with the given `type` and `argument`.
ast_matchers::StatementMatcher getSmartPointerMemberCallExprInTypeWithArgument(
    const char *name, ast_matchers::TypeMatcher type,
    ast_matchers::StatementMatcher argument);

/// Define matcher to match the member function call with `name` of a smart
/// pointer with the given `type` and no arguments.
ast_matchers::StatementMatcher
getSmartPointerMemberCallExprInType(const char *name,
                                    ast_matchers::TypeMatcher type);

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

#endif // LLVM_CLANG_TOOLS_EXTRA_CLANG_TIDY_SMARTPOINTERSAFETY_SMARTPOINTERTYPEMATCHER_H

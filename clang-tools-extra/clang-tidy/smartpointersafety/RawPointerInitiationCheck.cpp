//===--- RawPointerInitiationCheck.cpp - clang-tidy -----------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "RawPointerInitiationCheck.h"
#include "SmartPointerTypeMatcher.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ExprCXX.h"
#include "clang/ASTMatchers/ASTMatchFinder.h"

using namespace clang::ast_matchers;

namespace clang {
namespace tidy {
namespace smartpointersafety {

void RawPointerInitiationCheck::registerMatchers(MatchFinder *Finder) {
  // Matching the first argument with type of raw pointer
  auto argument = declRefExpr(hasType(isAnyPointer())).bind("ptr");

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

  // Matching function exit to generate summary and clear the record.
  Finder->addMatcher(functionDecl(), this);
}

void RawPointerInitiationCheck::check(const MatchFinder::MatchResult &Result) {
  // Report matched raw pointers and corresponding definitions.
  const auto *ptr = Result.Nodes.getNodeAs<DeclRefExpr>("ptr");
  if (ptr) {
    diag(ptr->getLocation(), "Initiating smart pointer with raw pointer.");
    const auto *decl = ptr->getDecl();
    diag(decl->getLocation(),
         "Referenced raw pointer defined here:", DiagnosticIDs::Note);
    ++matchedRawPointers[decl];
    return;
  }

  // If a new function start is matched, generate appearance summaries for the
  // recorded raw pointers and clear the record.
  generateFunctionSummary();
  matchedRawPointers.clear();
}

void RawPointerInitiationCheck::onStartOfTranslationUnit() {
  matchedRawPointers.clear();
}

void RawPointerInitiationCheck::onEndOfTranslationUnit() {
  // Make summary for the last function, and prepare for next TU.
  generateFunctionSummary();
  matchedRawPointers.clear();
}

void RawPointerInitiationCheck::generateFunctionSummary() {
  for (auto matches : matchedRawPointers) {
    // Generate warnings only for those appear more than once.
    if (matches.second > 1) {
      diag(matches.first->getLocation(),
           std::string("Raw pointer used for initiating different smart "
                       "pointers for ") +
               (matches.second == 2
                    ? std::string("twice.")
                    : std::to_string(matches.second) + " times."));
    }
  }
}

} // namespace smartpointersafety
} // namespace tidy
} // namespace clang

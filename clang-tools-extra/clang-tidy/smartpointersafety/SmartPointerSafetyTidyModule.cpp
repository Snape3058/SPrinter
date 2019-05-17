//===-- SmartPointerSafetyModule.cpp - clang-tidy -------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "../ClangTidy.h"
#include "../ClangTidyModule.h"
#include "../ClangTidyModuleRegistry.h"
#include "AutoptrInContainerCheck.h"
#include "AutoptrOwnershipTransferCheck.h"
#include "DeallocatingObserverPointerCheck.h"
#include "NonAllocatedMemoryInitiationCheck.h"
#include "PrivateAutoptrInClassCheck.h"
#include "RawPointerInitiationCheck.h"
#include "TypeMismatchInitiationCheck.h"
#include "UncheckedLockedWeakPointerCheck.h"
#include "UndeallocatedReleasedPointerCheck.h"

namespace clang {
namespace tidy {
namespace smartpointersafety {

/// A module containing checks of the C++ Core Guidelines
class SmartPointerSafetyModule : public ClangTidyModule {
public:
  void addCheckFactories(ClangTidyCheckFactories &CheckFactories) override {
    CheckFactories.registerCheck<AutoptrInContainerCheck>(
        "smartpointersafety-autoptr-in-container");
    CheckFactories.registerCheck<AutoptrOwnershipTransferCheck>(
        "smartpointersafety-autoptr-ownership-transfer");
    CheckFactories.registerCheck<NonAllocatedMemoryInitiationCheck>(
        "smartpointersafety-non-allocated-memory-initiation");
    CheckFactories.registerCheck<PrivateAutoptrInClassCheck>(
        "smartpointersafety-private-autoptr-in-class");
    CheckFactories.registerCheck<RawPointerInitiationCheck>(
        "smartpointersafety-raw-pointer-initiation");
    CheckFactories.registerCheck<DeallocatingObserverPointerCheck>(
        "smartpointersafety-deallocating-observer-pointer");
    CheckFactories.registerCheck<TypeMismatchInitiationCheck>(
        "smartpointersafety-type-mismatch-initiation");
    CheckFactories.registerCheck<UncheckedLockedWeakPointerCheck>(
        "smartpointersafety-unchecked-locked-weak-pointer");
    CheckFactories.registerCheck<UndeallocatedReleasedPointerCheck>(
        "smartpointersafety-undeallocated-released-pointer");
  }
};

// Register the LLVMTidyModule using this statically initialized variable.
static ClangTidyModuleRegistry::Add<SmartPointerSafetyModule>
    X("smartpointersafety-module", "Adds checks for the smart pointer safety.");

} // namespace smartpointersafety

// This anchor is used to force the linker to link in the generated object file
// and thus register the SmartPointerSafetyModule.
volatile int SmartPointerSafetyModuleAnchorSource = 0;

} // namespace tidy
} // namespace clang

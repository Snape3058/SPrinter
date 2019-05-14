set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidySmartPointerSafetyModule
  NonAllocatedMemoryInitiationCheck.cpp
  RawPointerInitiationCheck.cpp
  SmartPointerSafetyTidyModule.cpp
  SmartPointerTypeMatcher.cpp
  TypeMismatchInitiationCheck.cpp
  UncheckedLockedWeakPointerCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )

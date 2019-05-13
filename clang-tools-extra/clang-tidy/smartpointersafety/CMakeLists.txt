set(LLVM_LINK_COMPONENTS support)

add_clang_library(clangTidySmartPointerSafetyModule
  RawPointerInitiationCheck.cpp
  SmartPointerSafetyTidyModule.cpp
  SmartPointerTypeMatcher.cpp
  TypeMismatchInitiationCheck.cpp

  LINK_LIBS
  clangAST
  clangASTMatchers
  clangBasic
  clangLex
  clangTidy
  clangTidyUtils
  )

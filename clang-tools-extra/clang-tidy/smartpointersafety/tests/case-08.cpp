#include "env.h"

namespace {
class UseAutoPtrInClassWithDefaultCopyConstructor {
  auto_ptr<obj_ty> ap;

public:
  UseAutoPtrInClassWithDefaultCopyConstructor(
      UseAutoPtrInClassWithDefaultCopyConstructor &) = default;
};
} // namespace

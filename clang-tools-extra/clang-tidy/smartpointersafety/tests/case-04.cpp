#include "env.h"

namespace {
class UseAutoPtrInClassWithoutCopyConstructor {
  auto_ptr<obj_ty> ap;
};
} // namespace

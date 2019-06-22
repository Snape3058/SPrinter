#include "env.h"

/* no warnings */

namespace {
class UseAutoPtrInClassWithDefaultCopiers {
  auto_ptr<obj_ty> ap;

public:
  UseAutoPtrInClassWithDefaultCopiers &
  operator=(UseAutoPtrInClassWithDefaultCopiers &) = default;
  UseAutoPtrInClassWithDefaultCopiers(UseAutoPtrInClassWithDefaultCopiers &) =
      default;
};
} // namespace

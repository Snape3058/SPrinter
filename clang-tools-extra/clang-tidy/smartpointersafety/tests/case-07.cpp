#include "env.h"

namespace {
class UseAutoPtrInClassWithDefaultCopyAssignmentOperator {
  auto_ptr<obj_ty> ap;

public:
  UseAutoPtrInClassWithDefaultCopyAssignmentOperator &
  operator=(UseAutoPtrInClassWithDefaultCopyAssignmentOperator &) = default;
};
} // namespace

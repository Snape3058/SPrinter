#include "env.h"

namespace {
class UseAutoPtrInClassWithConstructor {
  auto_ptr<obj_ty> ap;

public:
  explicit UseAutoPtrInClassWithConstructor(auto_ptr<obj_ty> p) : ap(p) {}
};
} // namespace

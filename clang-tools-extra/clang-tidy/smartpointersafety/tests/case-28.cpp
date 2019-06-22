#include "env.h"

namespace {
void ConstructSmartPointerWithObjectFieldMemory() {
  obj_ty o;
  auto_ptr<int> ap(&o.use());
  unique_ptr<int> up(&o.use());
  shared_ptr<int> sp(&o.use());
}
} // namespace

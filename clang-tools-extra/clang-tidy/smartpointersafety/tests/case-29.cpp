#include "env.h"

namespace {
void ConstructSmartPointerWithObjectFieldMemoryAddress() {
  obj_ty o;
  auto_ptr<int> ap(&o.x);
  unique_ptr<int> up(&o.x);
  shared_ptr<int> sp(&o.x);
}
} // namespace

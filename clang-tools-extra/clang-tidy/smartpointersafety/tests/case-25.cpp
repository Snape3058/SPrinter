#include "env.h"

namespace {
void ConstructSmartPointerWithStackMemory() {
  obj_ty o;
  auto_ptr<obj_ty> ap(&o);
  unique_ptr<obj_ty> up(&o);
  shared_ptr<obj_ty> sp(&o);
}
} // namespace

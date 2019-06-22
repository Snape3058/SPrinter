#include "env.h"

namespace {
obj_ty o;
void ConstructSmartPointerWithGlobalMemory() {
  auto_ptr<obj_ty> ap(&o);
  unique_ptr<obj_ty> up(&o);
  shared_ptr<obj_ty> sp(&o);
}
} // namespace

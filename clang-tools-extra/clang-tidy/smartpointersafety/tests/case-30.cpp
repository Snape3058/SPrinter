#include "env.h"

namespace {
void ConstructSmartPointerWithUnknownPointerOffset() {
  obj_ty a[3];
  auto_ptr<obj_ty> ap(a + 1);
  unique_ptr<obj_ty> up(a + 1);
  shared_ptr<obj_ty> sp(a + 1);
}
} // namespace

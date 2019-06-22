#include "env.h"

namespace {
void DeleteManagedMemoryViaObserver() {
  auto_ptr<obj_ty> ap(new obj_ty);
  delete ap.get();
  unique_ptr<obj_ty> up = make_unique<obj_ty>();
  delete up.get();
  shared_ptr<obj_ty> sp = make_shared<obj_ty>();
  delete sp.get();
}
} // namespace

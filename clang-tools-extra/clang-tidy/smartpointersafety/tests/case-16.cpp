#include "env.h"

namespace {
void DeleteManagedMemoryViaObserverAssignedRawPointer() {
  auto_ptr<obj_ty> ap(new obj_ty);
  obj_ty *rpa = ap.get();
  delete rpa;
  unique_ptr<obj_ty> up = make_unique<obj_ty>();
  obj_ty *rpu = up.get();
  delete rpu;
  shared_ptr<obj_ty> sp = make_shared<obj_ty>();
  obj_ty *rps = sp.get();
  delete rps;
}
} // namespace

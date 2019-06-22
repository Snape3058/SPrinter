#include "env.h"

namespace {
void UsingWeakPtrDirectlyAfterLockedToSharedPtr() {
  shared_ptr<obj_ty> sp = make_shared<obj_ty>();
  weak_ptr<obj_ty> wp = sp;
  auto use = wp.lock();
  use->use();
  (void)use->x;
  (void)*use;
}
} // namespace

#include "env.h"

namespace {
void UsingWeakPtrDirectlyAfterLockedReturned() {
  shared_ptr<obj_ty> sp = make_shared<obj_ty>();
  weak_ptr<obj_ty> wp(sp);
  (wp.lock())->use();
  (void)wp.lock()->x;
  (void)*wp.lock();
}
} // namespace

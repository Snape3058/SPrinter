#include "env.h"

namespace {
void UsingWeakPtrAfterLockedWithUncorrelatedCheck(bool flag) {
  shared_ptr<obj_ty> sp = make_shared<obj_ty>();
  weak_ptr<obj_ty> wp = sp;
  auto use = wp.lock();

  // good, check before use.
  if (use)
    *use;

  // good, secure definition and usage.
  if (auto use = wp.lock())
    *use;

  // bad, uncorrelated check.
  if (flag)
    *use;

  // bad, uncorrelated check on other locked pointers.
  if (use) {
    auto newuse = wp.lock();
    *newuse;
  }

  // good, check before use.
  if (use) {
    if (flag) {
      *use;
    }
  }
}
} // namespace

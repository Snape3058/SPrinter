#include "env.h"

namespace {
void ReleaseOwnershipWithPointerUsed() {
  auto_ptr<obj_ty> ap(new obj_ty);
  ap.release()->use();
  (void)*ap.release();
  (void)ap.release();
  unique_ptr<obj_ty> up = make_unique<obj_ty>();
  up.release()->use();
  (void)*up.release();
  (void)up.release();
}
} // namespace

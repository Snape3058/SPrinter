#include "env.h"

namespace {
void ReleaseOwnershipWithoutPointerUsed() {
  auto_ptr<obj_ty> ap(new obj_ty);
  ap.release();
  unique_ptr<obj_ty> up = make_unique<obj_ty>();
  up.release();
}
} // namespace

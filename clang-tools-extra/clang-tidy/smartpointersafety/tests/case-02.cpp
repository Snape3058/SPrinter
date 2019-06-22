#include "env.h"

namespace {
void UseAfterAutoPtrAssignment() {
  auto_ptr<obj_ty> sp1(new obj_ty);
  auto_ptr<obj_ty> sp2 = sp1;
  *sp1;
}
} // namespace

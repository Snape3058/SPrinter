#include "env.h"

namespace {
void MultipleRawPointersInitiation() {
  obj_ty *p1 = new obj_ty;
  obj_ty *p2 = new obj_ty;
  auto_ptr<obj_ty> ap1(p1);
  auto_ptr<obj_ty> ap2(p2);
  shared_ptr<obj_ty> sp1(p1);
  shared_ptr<obj_ty> sp2(p2);
  unique_ptr<obj_ty> up1(p1);
  unique_ptr<obj_ty> up2(p2);
}
} // namespace

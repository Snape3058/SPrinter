#include "env.h"

namespace {
void RawPointerInitiation() {
  obj_ty *p = new obj_ty;
  unique_ptr<obj_ty> up1(p);
  shared_ptr<obj_ty> sp1(p);
  shared_ptr<obj_ty> sp2(sp1);
  auto_ptr<obj_ty> ap1(p);
  unique_ptr<obj_ty> up2;
  auto_ptr<obj_ty> ap2;
  up2.reset(p);
  ap2.reset(p);
  sp2.reset(p);
}
} // namespace

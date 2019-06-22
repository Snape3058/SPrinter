#include "env.h"

namespace {
void TypeMismatchInitiationWithNew() {
  auto_ptr<obj_ty> ap0good(new obj_ty);
  ap0good.reset(new obj_ty);
  auto_ptr<obj_ty> ap1bad(new obj_ty[3]);
  ap1bad.reset(new obj_ty[3]);
  unique_ptr<obj_ty> up0good(new obj_ty);
  up0good.reset(new obj_ty);
  unique_ptr<obj_ty> up1bad(new obj_ty[3]);
  up1bad.reset(new obj_ty[3]);
  unique_ptr<obj_ty[]> up2bad(new obj_ty);
  up2bad.reset(new obj_ty);
  unique_ptr<obj_ty[]> up3good(new obj_ty[3]);
  up3good.reset(new obj_ty[3]);
  shared_ptr<obj_ty> sp0good(new obj_ty);
  sp0good.reset(new obj_ty);
  shared_ptr<obj_ty> sp1bad(new obj_ty[3]);
  sp1bad.reset(new obj_ty[3]);
  shared_ptr<obj_ty[]> sp2bad(new obj_ty);
  sp2bad.reset(new obj_ty);
  shared_ptr<obj_ty[]> sp3good(new obj_ty[3]);
  sp3good.reset(new obj_ty[3]);
}
} // namespace

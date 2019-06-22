#include "env.h"

namespace {
void RawPointerReseting() {
  unique_ptr<obj_ty> sp1;
  unique_ptr<obj_ty> sp2;
  obj_ty *p = new obj_ty;
  sp1.reset(p);
  sp2.reset(p);
}
} // namespace

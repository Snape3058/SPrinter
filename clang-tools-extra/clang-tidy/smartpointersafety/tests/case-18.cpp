#include "env.h"

namespace {
void RawPointerConstruction() {
  obj_ty *p = new obj_ty;
  unique_ptr<obj_ty> sp1(p);
  unique_ptr<obj_ty> sp2(p);
}
} // namespace

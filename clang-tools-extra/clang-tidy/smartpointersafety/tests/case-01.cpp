#include "env.h"

namespace {
void foo(auto_ptr<obj_ty>) {}

void UseAfterAutoPtrAsArgument() {
  auto_ptr<obj_ty> sp(new obj_ty);
  foo(sp);
  sp->use();
}
} // namespace

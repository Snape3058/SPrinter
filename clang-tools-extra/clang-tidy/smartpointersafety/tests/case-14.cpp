#include "env.h"

namespace {
// Test all kinds of statements.
void ReleaseOwnershipInControlStatements(bool flag) {
  unique_ptr<obj_ty> ap(new obj_ty);
  int x = 0;
  if (ap.release())
    ;
  if (flag)
    ap.release();
  if (flag)
    ;
  else
    ap.release();
  while (ap.release())
    continue;
  while (flag)
    ap.release();
  do
    continue;
  while (ap.release());
  do
    ap.release();
  while (flag);
  for (ap.release();;)
    continue;
  for (; ap.release();)
    continue;
  for (;; ap.release())
    continue;
  for (;;)
    ap.release();
  for (auto &x : vector<unique_ptr<obj_ty>>())
    x.release();
  switch (x) {
  default:
    ap.release();
  }
  switch (x) {
  case true:
    ap.release();
  default:
    break;
  }

  // StmtExpr should not be matched.
  void *p = ({
    auto_ptr<obj_ty> sp(new obj_ty);
    sp.release();
  });
  (void)p;
}
} // namespace

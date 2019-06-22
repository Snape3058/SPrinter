#include "env.h"

/* no warnings */

namespace {
string *foo(const char *s) { return new string(s); }
void ConstructSmartPointerWithCStyledStringInNewOperator() {
  unique_ptr<string> up1(new string("c-styled-sting")); // good, not an array
  unique_ptr<string> up2(foo("c-styled-string"));       // good, not an array
}
} // namespace

#include "env.h"

/* no warnings */

namespace {
class UseAutoPtrInClassWithoutCopyConstructorWhichAutoPtrIsProtected {
protected:
  auto_ptr<obj_ty> ap; // good, protected field
};
} // namespace

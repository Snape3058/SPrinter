#include "env.h"

/* no warnings */

namespace {
class UseAutoPtrInClassWithoutCopyConstructorWhichAutoPtrIsPublic {
public:
  auto_ptr<obj_ty> ap; // good, public field
};
} // namespace

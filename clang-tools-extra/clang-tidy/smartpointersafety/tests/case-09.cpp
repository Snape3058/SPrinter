#include "env.h"

namespace {
template <typename T> class UseAutoPtrInClassTemplateWithoutCopyConstructor {
  auto_ptr<T> ap;
};
} // namespace

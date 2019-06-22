#include "env.h"

namespace {
void ConstructSmartPointerWithConstantPointerValue() {
  auto_ptr<int> ap((int *)0xfeeefeeefeeefeee);
  unique_ptr<int> up((int *)0xfeeefeeefeeefeee);
  shared_ptr<int> sp((int *)0xfeeefeeefeeefeee);
}
} // namespace

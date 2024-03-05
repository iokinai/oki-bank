#include "extensions.hxx"

namespace okibank {

// First = ecx, Second = edx
std::pair<uint32_t, uint32_t> get_available_extensions() noexcept {
  std::pair<uint32_t, uint32_t> exts;

  asm(R"(
    movl $0x00000001, %%eax
    cpuid
    movl %%ecx, %0
    movl %%edx %1
  )"
      : "=r"(exts.first), "=r"(exts.second)
      :
      : "%eax", "%ecx");

  return exts;
}

} // namespace okibank
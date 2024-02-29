#include "aes_ni.hxx"
#include <cstdint>

namespace okibank::aes {

bool has_aes_ni() noexcept {
  uint32_t has_ni;

  asm(R"(
    movl $0x00000001, %%eax
    CPUID
    movl %%ecx, %0
  )"
      : "=r"(has_ni)
      :
      : "%eax", "%ecx");

  return (has_ni & 0x2000000) == 0x2000000;
}

} // namespace okibank::aes
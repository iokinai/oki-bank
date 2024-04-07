#include "aes128_ni.hxx"
#include "../aes_common.hxx"
#include "../aes_math.hxx"
#include <array>
#include <cstdint>
#include <vector>

namespace okibank::aes {

[[maybe_unused]] static void
__vector_push_back_state_range(std::vector<uint8_t> &vec, const state &st) {
  for (const auto &s : st) {
    vec.push_back(s);
  }
}

std::array<std::uint8_t, AES128_STATE_SIZE>
encrypt_block_aes128(const std::array<std::uint8_t, AES128_STATE_SIZE> &block,
                     const std::array<std::uint8_t, AES128_STATE_SIZE> &key) {

  alignas(16) __int128 temp_num = 0;

  state st(block);

  asm volatile(R"(
      movdqu %1, %%xmm1
      movdqu %2, %%xmm2

      aesenc %%xmm1, %%xmm2

      movdqu %%xmm1, %0
    )"
               : "=g"(temp_num)
               : "g"(static_cast<__int128>(st)),
                 "g"(array_into_int128(const_cast<uint8_t *>(key.data())))
               : "rcx", "rbx", "xmm1", "xmm2");

  return int128_into_array(temp_num);
}

} // namespace okibank::aes
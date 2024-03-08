#include "aes128_ni.hxx"
#include "../aes_common.hxx"
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

std::vector<uint8_t>
encrypt_aes128(std::string data,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &key,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &IV) {

  std::vector<state> states = split_into_aes_cbc_blocks(data);

  std::vector<state> result_states;
  std::vector<uint8_t> result;
  uint8_t temp_bytes[AES128_STATE_SIZE];

  std::array<std::uint8_t, AES128_STATE_SIZE> prev = IV;

  for (auto &st : states) {
    st ^= prev;

    asm volatile(R"(
      movdqu %1, %%xmm1
      movdqu %2, %%xmm2
      movq $0, %%rcx

      aesloop:

      aesenc %%xmm1, %%xmm2

      inc %%rcx

      movq $9, %%rbx
      cmpq %%rcx, %%rbx
      jnl aesloop

      aesenclast %%xmm1, %%xmm2

      movdqu %%xmm1, %0
    )"
                 : "=g"(temp_bytes)
                 : "g"(st.get_bytes().data()), "g"(key.data())
                 : "rcx", "rbx", "xmm1", "xmm2");

    prev = std::to_array(temp_bytes);

    result_states.push_back(state(std::to_array(temp_bytes)));
  }

  for (auto &rs : result_states) {
    __vector_push_back_state_range(result, rs);
  }

  return result;
}

} // namespace okibank::aes
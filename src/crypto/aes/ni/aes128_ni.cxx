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

std::vector<uint8_t>
encrypt_aes128(std::string data,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &key,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &IV) {

  std::vector<state> states = split_into_aes_cbc_blocks(data);

  std::vector<state> result_states;
  std::vector<uint8_t> result;
  alignas(16) __int128 temp_num = 0;

  std::array<std::uint8_t, AES128_STATE_SIZE> prev = IV;

  alignas(16) __int128 key_data =
      array_into_int128(const_cast<uint8_t *>(key.data()));

  for (auto &st : states) {
    st ^= prev;

    alignas(16) __int128 state_data =
        array_into_int128(const_cast<uint8_t *>(st.get_bytes().data()));

    /*

          movq $0, %%rcx

          aesloop:

          aesenc %%xmm1, %%xmm2

          inc %%rcx

          movq $9, %%rbx
          cmpq %%rcx, %%rbx
          jnl aesloop


    */

    asm volatile(R"(
      movdqu %1, %%xmm1
      movdqu %2, %%xmm2

      aesenc %%xmm1, %%xmm2

      movdqu %%xmm1, %0
    )"
                 : "=g"(temp_num)
                 : "g"(state_data), "g"(key_data)
                 : "rcx", "rbx", "xmm1", "xmm2");

    prev = int128_into_array(temp_num);

    result_states.push_back(state(prev));
  }

  for (auto &rs : result_states) {
    __vector_push_back_state_range(result, rs);
  }

  return result;
}

} // namespace okibank::aes
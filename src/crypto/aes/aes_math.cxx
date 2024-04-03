#include "aes_math.hxx"
#include "aes_consts.hxx"
#include <array>
#include <cstdint>

namespace okibank::aes {

inline constexpr uint8_t add(uint8_t v1, uint8_t v2) noexcept {
  return v1 ^ v2;
}

inline constexpr uint8_t mul(uint8_t a, uint8_t b) noexcept {
  uint8_t result = 0;
  uint8_t mask = 0x01;
  for (int i = 0; i < 8; ++i) {
    if (b & mask) {
      result ^= a;
    }
    bool high_bit_set = a & 0x80;
    a <<= 1;
    if (high_bit_set) {
      a ^= 0x1b;
    }
    mask <<= 1;
  }
  return result;
}

__int128 array_into_int128(uint8_t arr[AES128_STATE_SIZE]) noexcept {
  __int128 result = 0;

  for (int i = 0; i < AES128_STATE_SIZE; ++i) {
    result = (result << 8) | arr[i];
  }

  return result;
}

std::array<uint8_t, AES128_STATE_SIZE> int128_into_array(__int128 n) noexcept {
  std::array<uint8_t, AES128_STATE_SIZE> arr;

  for (int i = 0; i < AES128_STATE_SIZE; ++i) {
    arr[15 - i] = (n >> (i * 8)) & 0xFF;
  }

  return arr;
}

} // namespace okibank::aes
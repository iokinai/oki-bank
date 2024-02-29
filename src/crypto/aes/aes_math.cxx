#include "aes_math.hxx"

namespace okibank::aes {

inline constexpr byte add(byte v1, byte v2) noexcept {
  return v1 ^ v2;
}

inline constexpr byte mul(byte a, byte b) noexcept {
  byte result = 0;
  byte mask = 0x01;
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

} // namespace okibank::aes
#ifndef CRYPTO_AES_MATH_HXX
#define CRYPTO_AES_MATH_HXX

#include <array>
#include <cstdint>

namespace okibank::aes {

inline constexpr uint8_t add(uint8_t a, uint8_t b) noexcept;
inline constexpr uint8_t mul(uint8_t a, uint8_t b) noexcept;

__int128 array_into_int128(uint8_t arr[16]) noexcept;
std::array<uint8_t, 16> int128_into_array(__int128 n) noexcept;

} // namespace okibank::aes

#endif
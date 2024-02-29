#ifndef CRYPTO_AES_MATH_HXX
#define CRYPTO_AES_MATH_HXX

#include "aes_types.hxx"

namespace okibank::aes {

inline constexpr byte add(byte a, byte b) noexcept;
inline constexpr byte mul(byte a, byte b) noexcept;

} // namespace okibank::aes

#endif
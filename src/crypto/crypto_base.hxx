#ifndef CRYPTO_CRYPTO_BASE_HXX
#define CRYPTO_CRYPTO_BASE_HXX

#include <concepts>
#include <cstdint>

namespace okibank {

template <std::integral T> T swap_endian(T u);

} // namespace okibank

#endif
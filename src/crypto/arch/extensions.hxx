#ifndef CRYPTO_ARCH_EXTENSIONS_HXX
#define CRYPTO_ARCH_EXTENSIONS_HXX

#include <cstdint>
#include <utility>

namespace okibank {

std::pair<uint32_t, uint32_t> get_available_extensions() noexcept;

} // namespace okibank

#endif
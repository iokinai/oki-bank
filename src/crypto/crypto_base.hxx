#ifndef CRYPTO_CRYPTO_BASE_HXX
#define CRYPTO_CRYPTO_BASE_HXX

#include "enc_block.hxx"
#include "init_vector.hxx"
#include <concepts>
#include <list>

namespace okibank {

std::list<enc_block> split_into_sha256_blocks(std::string expr);

template <std::integral T> T swap_endian(T u);

constexpr inline init_vector init_values_h() noexcept;

} // namespace okibank

#endif
#ifndef CRYPTO_AES_NI_AES128_NI_HXX
#define CRYPTO_AES_NI_AES128_NI_HXX

#include "../aes_consts.hxx"
#include <array>
#include <cstdint>

namespace okibank::aes {

std::array<std::uint8_t, AES128_STATE_SIZE>
encrypt_block_aes128(const std::array<std::uint8_t, AES128_STATE_SIZE> &block,
                     const std::array<std::uint8_t, AES128_STATE_SIZE> &key);

} // namespace okibank::aes

#endif
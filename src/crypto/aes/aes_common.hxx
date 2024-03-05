#ifndef CRYPTO_AES_AES_COMMON_HXX
#define CRYPTO_AES_AES_COMMON_HXX

#include "aes_types.hxx"
#include <string>
#include <vector>
namespace okibank::aes {

const byte AES128_ROUNDS = 10;
const byte AES128_KEY_LEN = 4;
const byte AES128_BLOCK_SIZE = 4;

std::vector<std::array<uint32_t, AES128_BLOCK_SIZE>>
split_into_aes_cbc_blocks(std::string value) noexcept;

} // namespace okibank::aes

#endif
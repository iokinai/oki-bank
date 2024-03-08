#ifndef CRYPTO_AES_AES_CONSTS_HXX
#define CRYPTO_AES_AES_CONSTS_HXX

#include <cstdint>

namespace okibank::aes {

using byte = uint8_t;

const byte AES128_ROUNDS = 10;
const byte AES128_KEY_LEN = 4;
const byte AES128_BLOCK_SIZE = 4;
const byte AES128_STATE_SIZE = 16;

} // namespace okibank::aes

#endif
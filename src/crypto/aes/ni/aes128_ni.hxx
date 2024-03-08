#ifndef CRYPTO_AES_NI_AES128_NI_HXX
#define CRYPTO_AES_NI_AES128_NI_HXX

#include "../aes_consts.hxx"
#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace okibank::aes {

std::vector<uint8_t>
encrypt_aes128(std::string data,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &key,
               const std::array<std::uint8_t, AES128_STATE_SIZE> &IV);

} // namespace okibank::aes

#endif
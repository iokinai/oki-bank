#ifndef CRYPTO_AES_AES_COMMON_HXX
#define CRYPTO_AES_AES_COMMON_HXX

#include "state.hxx"
#include <string>
#include <vector>

namespace okibank::aes {

std::vector<state> split_into_aes_cbc_blocks(std::string value) noexcept;

} // namespace okibank::aes

#endif
#ifndef CRYPTO_CRYPTO_BASE_HXX
#define CRYPTO_CRYPTO_BASE_HXX

#include "enc_block.hxx"
#include <list>

namespace okibank {

std::list<enc_block> split_into_sha256_blocks(std::string expr);

} // namespace okibank

#endif
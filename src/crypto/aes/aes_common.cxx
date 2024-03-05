#include "aes_common.hxx"
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace okibank::aes {

static inline uint32_t
__bytes_into_uint32_t(std::array<uint8_t, sizeof(uint32_t)> bytes) {
  uint32_t val = 0;
  return val << sizeof(uint8_t) | bytes[3] << sizeof(uint8_t) |
         bytes[2] << sizeof(uint8_t) | bytes[1] << sizeof(uint8_t) | bytes[0];
}

template <int values_count>
static std::array<uint8_t, values_count> __values_from_string(std::string str,
                                                              int start) {
  if (values_count <= 0) {
    throw std::invalid_argument("values_count should be more than zero!");
  }

  std::array<uint8_t, values_count> res;

  for (std::size_t i{0}; i < values_count; ++i) {
    res[i] = str.at(start + i);
  }

  return res;
}

std::vector<std::array<uint32_t, AES128_BLOCK_SIZE>>
split_into_aes_cbc_blocks(std::string value) noexcept {
  int rounds = (value.length() + AES128_BLOCK_SIZE - 1) / AES128_BLOCK_SIZE;

  std::vector<std::array<uint32_t, AES128_BLOCK_SIZE>> blocks(rounds);

  for (std::size_t i{0}; i < rounds; ++i) {
    std::array<uint32_t, AES128_BLOCK_SIZE> block;

    for (std::size_t j{0}; j < AES128_BLOCK_SIZE; ++j) {
      std::array<uint8_t, sizeof(uint32_t)> values;

      try {
        values = __values_from_string<sizeof(uint32_t)>(value, i);
      } catch (std::invalid_argument) {
        return {};
      } catch (std::out_of_range) {
        return {};
      }

      block[j] = __bytes_into_uint32_t(values);
    }

    blocks.push_back(block);
  }

  return blocks;
}

} // namespace okibank::aes
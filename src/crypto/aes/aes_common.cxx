#include "aes_common.hxx"
#include "aes_consts.hxx"
#include "state.hxx"
#include <array>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace okibank::aes {

[[maybe_unused]] static inline uint32_t
__bytes_into_uint32_t(std::array<uint8_t, sizeof(uint32_t)> bytes) {
  uint32_t val = 0;
  return val << sizeof(uint8_t) | bytes[3] << sizeof(uint8_t) |
         bytes[2] << sizeof(uint8_t) | bytes[1] << sizeof(uint8_t) | bytes[0];
}

template <int values_count>
[[maybe_unused]] static std::array<uint8_t, values_count>
__values_from_string(std::string str, int start) {
  if (values_count <= 0) {
    throw std::invalid_argument("values_count should be more than zero!");
  }

  std::array<uint8_t, values_count> res;

  for (std::size_t i{0}; i < values_count; ++i) {
    try {
      res[i] = str.at(start + i);
    } catch (std::out_of_range) {
      for (std::size_t j = i; j < values_count; ++j) {
        res[j] = 0;
      }

      return res;
    }
  }

  return res;
}

std::vector<state> split_into_aes_cbc_blocks(std::string value) noexcept {
  int rounds = (value.length() + AES128_STATE_SIZE - 1) / AES128_STATE_SIZE;

  std::vector<state> blocks(rounds);

  for (std::size_t i{0}; i < rounds; ++i) {
    state block;

    try {
      block = __values_from_string<AES128_STATE_SIZE>(
          value, i + AES128_STATE_SIZE * i);
    } catch (std::invalid_argument) {
      return {};
    }

    blocks[i] = block;
  }

  return blocks;
}
} // namespace okibank::aes
#include "crypto_base.hxx"
#include "enc_block.hxx"
#include <bit>
#include <cstdint>
#include <iostream>

namespace okibank {

using str_iterator = std::string::iterator;

static void __fill_zeros(enc_block &block, byte first) {
  byte last_pos = block.get_last_pos();

  if (last_pos == enc_block::SIZE + 1) {
    return;
  }

  for (byte i = last_pos; i < enc_block::SIZE - 8; i++) {
    if (i == 0) {
      block[i] = first;
      continue;
    }

    block[i] = 0;
  }
}

static void __fill_size(enc_block &block, uint64_t size) {
  if constexpr (std::endian::native == std::endian::little) {
    size = swap_endian(size);
  }

  auto place = reinterpret_cast<uint64_t *>(block.get_data() + enc_block::SIZE -
                                            sizeof(uint64_t));
  *place = size;

  std::cout << *place << std::endl;
}

std::list<enc_block> split_into_sha256_blocks(std::string expr) {
  int size = (expr.length() + enc_block::SIZE - 1) / enc_block::SIZE;

  std::list<enc_block> blocks(size);

  str_iterator current = expr.begin();

  for (auto &block : blocks) {
    block.set_values(current, expr.end());
  }

  auto &last_block = blocks.back();

  if (last_block.get_last_pos() != enc_block::SIZE - 1) {
    __fill_zeros(last_block, 1 << 7);

    if (enc_block::SIZE - (last_block.get_last_pos() + 1) >= sizeof(uint64_t)) {
      __fill_size(last_block, expr.length());
    } else {
      last_block = blocks.emplace_back(0);
      __fill_zeros(last_block, 0);
      __fill_size(last_block, expr.length());
    }
  }

  return blocks;
}

template <std::integral T> T swap_endian(T u) {
  union {
    T u;
    unsigned char u8[sizeof(T)];
  } source, dest;

  source.u = u;

  for (size_t k = 0; k < sizeof(T); k++)
    dest.u8[k] = source.u8[sizeof(T) - k - 1];

  return dest.u;
}

constexpr inline init_vector init_values_h() noexcept {
  return {
      0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
      0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19,
  };
}

template uint8_t swap_endian(uint8_t val);

template uint16_t swap_endian(uint16_t val);

template uint32_t swap_endian(uint32_t val);

template uint64_t swap_endian(uint64_t val);

} // namespace okibank
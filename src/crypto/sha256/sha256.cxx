#include "sha256.hxx"
#include "../crypto_base.hxx"
#include <array>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <ios>
#include <sstream>
#include <vector>

namespace okibank::sha256 {

namespace {

using str_iterator = std::string::iterator;

inline uint32_t rotr(uint32_t x, uint32_t n) noexcept {
  return (x >> n) | (x << ((sizeof(uint32_t) * 8) - n));
}

inline uint32_t low_sigma0(uint32_t x) noexcept {
  return rotr(x, 7) ^ rotr(x, 18) ^ (x >> 3);
}

inline uint32_t low_sigma1(uint32_t x) noexcept {
  return rotr(x, 17) ^ rotr(x, 19) ^ (x >> 10);
}

inline uint32_t up_sigma0(uint32_t x) noexcept {
  return rotr(x, 2) ^ rotr(x, 13) ^ rotr(x, 22);
}

inline uint32_t up_sigma1(uint32_t x) noexcept {
  return rotr(x, 6) ^ rotr(x, 11) ^ rotr(x, 25);
}

inline uint32_t ch(uint32_t x, uint32_t y, uint32_t z) noexcept {
  return (x & y) ^ (~x & z);
}

inline uint32_t maj(uint32_t x, uint32_t y, uint32_t z) noexcept {
  return (x & y) ^ (x & z) ^ (y & z);
}

static void __fill_zeros(sha256_block &block, byte first) {
  byte last_pos = block.get_last_pos();

  if (last_pos == sha256_block::SIZE - 1) {
    return;
  }

  block[last_pos] = first;

  for (byte i = last_pos + 1; i < sha256_block::SIZE - sizeof(uint64_t); i++) {
    block[i] = 0;
  }
}

static void __fill_size(sha256_block &block, uint64_t size) noexcept {
  if constexpr (std::endian::native == std::endian::little) {
    size = swap_endian(size);
  }

  auto place = reinterpret_cast<uint64_t *>(
      block.get_data() + sha256_block::SIZE - sizeof(uint64_t));
  *place = size;
}

static std::array<uint32_t, 64>
__generate_message_schedule(const sha256_block &block) {
  std::array<uint32_t, 64> ms;

  for (int t{0}; t < 16; ++t) {
    ms[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) |
            (block[t * 4 + 2] << 8) | (block[t * 4 + 3]);
  }

  for (int t = 16; t < sha256_block::SIZE; ++t) {
    ms[t] =
        low_sigma1(ms[t - 2]) + ms[t - 7] + low_sigma0(ms[t - 15]) + ms[t - 16];
  }

  return ms;
}

const std::vector<sha256_block> split_into_sha256_blocks(std::string expr) {
  int size = (expr.length() + sha256_block::SIZE - 1) / sha256_block::SIZE;

  std::vector<sha256_block> blocks(size);

  str_iterator current = expr.begin();

  for (auto &block : blocks) {
    block.set_values(current, expr.end());
  }

  auto &last_block = blocks.back();

  if (last_block.get_last_pos() != sha256_block::SIZE - 1) {
    __fill_zeros(last_block, 1 << 7);

    if (sha256_block::SIZE - (last_block.get_last_pos() + 1) >=
        sizeof(uint64_t)) {
      __fill_size(last_block, expr.length() * 8);
    } else {
      last_block = blocks.emplace_back(0);
      __fill_zeros(last_block, 0);
      __fill_size(last_block, expr.length() * 8);
    }
  } else {
    blocks.emplace_back(0);
    last_block = blocks.back();
    __fill_zeros(last_block, 1 << 7);
    __fill_size(last_block, expr.length() * 8);
  }

  return blocks;
}

std::array<uint32_t, 8> process_hash(const std::vector<sha256_block> &blocks) {
  std::array<uint32_t, 8> values;
  uint32_t a, b, c, d, e, f, g, h;
  uint32_t T1, T2;

  for (size_t i{0}; i < 8; ++i) {
    values[i] = IV[i];
  }

  for (const auto &block : blocks) {
    std::array<uint32_t, 64> message_schedule =
        __generate_message_schedule(block);

    a = values[0];
    b = values[1];
    c = values[2];
    d = values[3];
    e = values[4];
    f = values[5];
    g = values[6];
    h = values[7];

    for (int t = 0; t < 64; ++t) {
      T1 = h + up_sigma1(e) + ch(e, f, g) + CONSTANTS[t] + message_schedule[t];
      T2 = up_sigma0(a) + maj(a, b, c);
      h = g;
      g = f;
      f = e;
      e = d + T1;
      d = c;
      c = b;
      b = a;
      a = T1 + T2;
    }

    values[0] += a;
    values[1] += b;
    values[2] += c;
    values[3] += d;
    values[4] += e;
    values[5] += f;
    values[6] += g;
    values[7] += h;
  }

  return values;
}

std::string sha256_result_into_str(const std::array<uint32_t, 8> &hash) {
  std::stringstream ss;

  for (size_t i{0}; i < 8; ++i) {
    ss << std::hex << std::setw(8) << std::setfill('0') << hash[i];
  }

  return ss.str();
}

} // namespace

std::array<uint32_t, 8> to_array(std::string value) {
  const std::vector<sha256_block> blocks = split_into_sha256_blocks(value);
  return process_hash(blocks);
}

std::string to_hex(std::string value) {
  return sha256_result_into_str(to_array(value));
}

} // namespace okibank::sha256
#include "crypto_base.hxx"
#include "enc_block.hxx"
#include <iostream>

namespace okibank {

using str_iterator = std::string::iterator;

static void __fill_zeros(enc_block &block) {
  byte last_pos = block.get_last_pos();

  if (last_pos == enc_block::SIZE + 1) {
    return;
  }

  for (byte i = last_pos; i < enc_block::SIZE - 8; i++) {
    block[i] = 0;
  }
}

static void __fill_size(enc_block &block, uint64_t size) {
  auto place =
      reinterpret_cast<uint64_t *>(block.get_data() + enc_block::SIZE - 8);
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
    __fill_zeros(last_block);
    __fill_size(last_block, expr.length());
  }

  return blocks;
}

} // namespace okibank
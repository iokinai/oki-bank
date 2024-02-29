#include "sha256_block.hxx"
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace okibank {

using vec_iterator = std::vector<byte>::iterator;
using init_iterator = std::initializer_list<byte>::iterator;

sha256_block::sha256_block() : data(new byte[SIZE]) {
}

sha256_block::sha256_block(const sha256_block &other)
    : data(new byte[SIZE]), __last_pos(other.__last_pos) {
  std::memcpy(this->data, other.data, SIZE);
}

sha256_block::sha256_block(std::initializer_list<byte> &&bytes)
    : sha256_block(bytes.begin(), bytes.end()) {
}

sha256_block::sha256_block(std::vector<byte> &bytes)
    : sha256_block(bytes.begin(), bytes.end()) {
}

sha256_block::sha256_block(sha256_block &&other)
    : data(other.data), __last_pos(std::move(other.__last_pos)) {
  other.data = nullptr;
}

sha256_block::sha256_block(byte init_value)
    : data(new byte(init_value)), __last_pos(sha256_block::SIZE - 1) {
}

sha256_block &sha256_block::operator=(const sha256_block &other) {
  if (this != &other) {
    delete[] data;
    data = new byte[SIZE];
    std::memcpy(data, other.data, SIZE);
    __last_pos = other.__last_pos;
  }

  return *this;
}

sha256_block &sha256_block::operator=(sha256_block &&other) {
  if (this != &other) {
    delete[] data;
    data = other.data;
    other.data = nullptr;
    __last_pos = std::move(other.__last_pos);
  }

  return *this;
}

byte sha256_block::get_last_pos() const noexcept {
  return __last_pos;
}

byte *sha256_block::get_data() const noexcept {
  return data;
}

byte &sha256_block::operator[](size_t position) {
  return const_cast<byte &>(static_cast<const sha256_block &>(*this)[position]);
}

const byte &sha256_block::operator[](size_t position) const {
  if (position >= SIZE) {
    throw std::out_of_range("Index should be less or equal to 63");
  }

  return data[position];
}

sha256_block::~sha256_block() {
  delete[] data;
}

} // namespace okibank
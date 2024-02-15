#include "enc_block.hxx"
#include <cstring>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace okibank {

using vec_iterator = std::vector<byte>::iterator;
using init_iterator = std::initializer_list<byte>::iterator;

enc_block::enc_block() : data(new byte[SIZE]) {
}

enc_block::enc_block(const enc_block &other)
    : data(new byte[SIZE]), __last_pos(other.__last_pos) {
  std::memcpy(this->data, other.data, SIZE);
}

enc_block::enc_block(std::initializer_list<byte> &&bytes)
    : enc_block(bytes.begin(), bytes.end()) {
}

enc_block::enc_block(std::vector<byte> &bytes)
    : enc_block(bytes.begin(), bytes.end()) {
}

enc_block::enc_block(enc_block &&other)
    : data(other.data), __last_pos(std::move(other.__last_pos)) {
  other.data = nullptr;
}

enc_block &enc_block::operator=(const enc_block &other) {
  if (this != &other) {
    delete[] data;
    data = new byte[SIZE];
    std::memcpy(data, other.data, SIZE);
    __last_pos = other.__last_pos;
  }

  return *this;
}

enc_block &enc_block::operator=(enc_block &&other) {
  if (this != &other) {
    delete[] data;
    data = other.data;
    other.data = nullptr;
    __last_pos = std::move(other.__last_pos);
  }

  return *this;
}

byte enc_block::get_last_pos() const noexcept {
  return __last_pos;
}

byte *enc_block::get_data() const noexcept {
  return data;
}

byte &enc_block::operator[](size_t position) {
  if (position >= SIZE) {
    throw std::out_of_range("Index should be less or equal to 63");
  }

  return data[position];
}

enc_block::~enc_block() {
  delete[] data;
}
} // namespace okibank
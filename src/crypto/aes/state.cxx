#include "state.hxx"
#include "aes_consts.hxx"
#include "aes_math.hxx"
#include <array>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace okibank::aes {

state::state() : bytes(std::array<uint8_t, ARRAY_SIZE>()) {
}

state::state(std::array<uint8_t, ARRAY_SIZE> other) : bytes(other) {
}

state::state(const state &other) : bytes(other.bytes) {
}

state::state(state &&other) : bytes(std::move(other.bytes)) {
}

state &state::operator=(uint8_t other[AES128_STATE_SIZE]) {
  std::copy(other, other + AES128_STATE_SIZE, std::begin(this->bytes));

  return *this;
}

state &state::operator=(std::array<uint8_t, ARRAY_SIZE> &other) {
  this->bytes = other;

  return *this;
}

state &state::operator=(const state &other) {
  if (this != &other) {
    this->bytes = other.bytes;
  }

  return *this;
}

state &state::operator=(state &&other) {
  if (this != &other) {
    this->bytes = std::move(other.bytes);
  }

  return *this;
}

constexpr inline uint8_t &state::operator[](int index) noexcept {
  return const_cast<uint8_t &>(const_cast<const state &>(*this)[index]);
}

constexpr inline const uint8_t &state::operator[](int index) const noexcept {
  return bytes[index];
}

constexpr inline uint8_t &state::operator[](int row, int col) noexcept {
  return const_cast<uint8_t &>(const_cast<const state &>(*this)[row, col]);
}

constexpr inline const uint8_t &state::operator[](int row,
                                                  int col) const noexcept {
  return bytes[row + 4 * col];
}

state state::operator^(
    const std::array<uint8_t, AES128_STATE_SIZE> &p) const noexcept {
  state new_state;

  for (std::size_t i{0}; i < AES128_STATE_SIZE; ++i) {
    new_state[i] = (*this)[i] ^ p[i];
  }

  return new_state;
}

state state::operator^(const state &p) const noexcept {
  return *this ^ p.get_bytes();
}

state &
state::operator^=(const std::array<uint8_t, AES128_STATE_SIZE> &p) noexcept {
  this->bytes = (*this ^ p).bytes;
  return *this;
}

state &state::operator^=(const state &p) noexcept {
  this->bytes = (*this ^ p).bytes;
  return *this;
}

const std::array<uint8_t, state::ARRAY_SIZE> &state::get_bytes() const {
  return this->bytes;
}

state::state_iterator::state_iterator(state::state_iterator::pointer iter)
    : ptr(iter) {
}

state::const_state_iterator::const_state_iterator(
    state::const_state_iterator::pointer iter)
    : ptr(iter) {
}

inline state::state_iterator state::begin() noexcept {
  return state::state_iterator(&bytes[0]);
}

state::const_state_iterator state::begin() const noexcept {
  return cbegin();
}

inline state::state_iterator state::end() noexcept {
  return state::state_iterator(&bytes[AES128_STATE_SIZE - 1]);
}

state::const_state_iterator state::end() const noexcept {
  return cend();
}

inline state::const_state_iterator state::cbegin() const noexcept {
  return state::const_state_iterator(&bytes[0]);
}

inline state::const_state_iterator state::cend() const noexcept {
  return state::const_state_iterator(&bytes[AES128_STATE_SIZE]);
}

state::operator __int128() const noexcept {
  return array_into_int128(const_cast<uint8_t *>(this->bytes.data()));
}

} // namespace okibank::aes
#ifndef CRYPTO_AES_STATE_HXX
#define CRYPTO_AES_STATE_HXX

#include "aes_consts.hxx"
#include <array>
#include <cstddef>
#include <cstdint>
#include <iterator>

namespace okibank::aes {

template <class It>
concept is_aes_state_iterator =
    requires(It it, typename It::pointer p, typename It::value_type v) {
      { it.ptr };
      { It(p) } -> std::same_as<It>;
      { v };
    };

template <is_aes_state_iterator It>
constexpr inline It::value_type operator*(It &obj) noexcept {
  return *(obj.ptr);
}

template <is_aes_state_iterator It>
constexpr inline It operator++(It &obj) noexcept {
  ++obj.ptr;
  return obj;
}

template <is_aes_state_iterator It>
constexpr inline It operator++(It &obj, int) noexcept {
  It temp = obj;
  ++(*obj);
  return temp;
}

template <is_aes_state_iterator It>
constexpr inline bool operator==(const It &obj, const It &other) noexcept {
  return obj.ptr == other.ptr;
}

template <is_aes_state_iterator It>
constexpr inline bool operator!=(const It &obj, const It &other) noexcept {
  return !(obj == other);
}

class state {
public:
  static const uint8_t ARRAY_SIZE = AES128_BLOCK_SIZE * 4;

private:
  alignas(16) std::array<uint8_t, ARRAY_SIZE> bytes;

public:
  state();
  state(std::array<uint8_t, ARRAY_SIZE> other);
  state(const state &other);
  state(state &&other);

  state &operator=(uint8_t other[AES128_STATE_SIZE]);
  state &operator=(std::array<uint8_t, ARRAY_SIZE> &other);
  state &operator=(const state &other);
  state &operator=(state &&other);

  constexpr inline uint8_t &operator[](int index) noexcept;
  constexpr inline const uint8_t &operator[](int index) const noexcept;

  constexpr inline uint8_t &operator[](int row, int col) noexcept;
  constexpr inline const uint8_t &operator[](int row, int col) const noexcept;

  state
  operator^(const std::array<uint8_t, AES128_STATE_SIZE> &p) const noexcept;
  state operator^(const state &p) const noexcept;

  state &operator^=(const std::array<uint8_t, AES128_STATE_SIZE> &p) noexcept;
  state &operator^=(const state &p) noexcept;

  const std::array<uint8_t, ARRAY_SIZE> &get_bytes() const;

  inline __int128 to_int128() const noexcept;

  class state_iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = uint8_t;
    using difference_type = std::ptrdiff_t;
    using pointer = uint8_t *;
    using reference = uint8_t &;

    state_iterator(pointer iter);

    pointer ptr;
  };

  class const_state_iterator {
  public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = const uint8_t;
    using difference_type = std::ptrdiff_t;
    using pointer = const uint8_t *;
    using reference = const uint8_t &;

    const_state_iterator(pointer iter);

    pointer ptr;
  };

  inline state_iterator begin() noexcept;

  const_state_iterator begin() const noexcept;

  inline state_iterator end() noexcept;

  const_state_iterator end() const noexcept;

  inline const_state_iterator cbegin() const noexcept;

  inline const_state_iterator cend() const noexcept;
};

} // namespace okibank::aes

#endif
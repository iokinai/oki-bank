#ifndef CACHE_CACHE_ITERATOR_HXX
#define CACHE_CACHE_ITERATOR_HXX

#include "../models/private_user.hxx"
#include <cstdint>
#include <iterator>

namespace okibank {

template <class T>
concept is_oki_iterator = requires(T val) {
  { val.current };
};

template <is_oki_iterator It> constexpr inline It &operator++(It &val) noexcept;

template <is_oki_iterator It>
constexpr inline It operator++(It &val, int) noexcept;

template <is_oki_iterator It> constexpr inline It &operator--(It &val) noexcept;

template <is_oki_iterator It>
constexpr inline It operator--(It &val, int) noexcept;

template <is_oki_iterator It>
int16_t operator-(const It &val1, const It &&val2) noexcept;

template <is_oki_iterator It>
bool operator==(const It &val1, const It &val2) noexcept;

template <is_oki_iterator It>
bool operator!=(const It &val1, const It &val2) noexcept;

template <is_oki_iterator It> It::reference operator*(It &val) noexcept;

class cache_iterator {
public:
  using value_type = private_user;
  using reference = private_user &;
  using pointer = private_user *;
  using iterator_category = std::input_iterator_tag;
  using difference_type = int16_t;

  explicit cache_iterator(pointer curr);

  constexpr inline pointer operator->() noexcept;

  pointer current;
};

class const_cache_iterator {
public:
  using value_type = const private_user;
  using reference = const private_user &;
  using pointer = const private_user *;
  using iterator_category = std::input_iterator_tag;
  using difference_type = int16_t;

  explicit const_cache_iterator(pointer curr);

  constexpr inline pointer operator->() noexcept;

  pointer current;
};

} // namespace okibank

#endif
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

class cache_iterator {
  private_user *current;

public:
  using value_type = private_user;
  using reference = private_user;
  using pointer = private_user *;
  using iterator_category = std::input_iterator_tag;
  using difference_type = int16_t;

  explicit cache_iterator(private_user *curr);

  constexpr inline private_user *get_current() noexcept;

  constexpr inline private_user &operator*() const noexcept;

  constexpr inline private_user *operator->() noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It &operator++(It &val) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It operator++(It &val, int) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It &operator--(It &val) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It operator--(It &val, int) noexcept;

  template <is_oki_iterator It>
  friend int16_t operator-(const It &val1, const It &&val2) noexcept;

  template <is_oki_iterator It>
  friend bool operator==(const It &val1, const It &val2) noexcept;

  template <is_oki_iterator It>
  friend bool operator!=(const It &val1, const It &val2) noexcept;
};

class const_cache_iterator {
  const private_user *current;

public:
  using value_type = private_user;
  using reference = private_user;
  using pointer = private_user *;
  using iterator_category = std::input_iterator_tag;
  using difference_type = int16_t;

  explicit const_cache_iterator(const private_user *curr);

  constexpr inline const private_user *get_current() const noexcept;

  constexpr inline const private_user &operator*() const noexcept;

  constexpr inline const private_user *operator->() noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It &operator++(It &val) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It operator++(It &val, int) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It &operator--(It &val) noexcept;

  template <is_oki_iterator It>
  friend constexpr inline It operator--(It &val, int) noexcept;

  template <is_oki_iterator It>
  friend int16_t operator-(const It &val1, const It &&val2) noexcept;

  template <is_oki_iterator It>
  friend bool operator==(const It &val1, const It &val2) noexcept;

  template <is_oki_iterator It>
  friend bool operator!=(const It &val1, const It &val2) noexcept;
};

} // namespace okibank

#endif
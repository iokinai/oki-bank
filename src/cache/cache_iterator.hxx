#ifndef CACHE_CACHE_ITERATOR_HXX
#define CACHE_CACHE_ITERATOR_HXX

#include "../models/private_user.hxx"

namespace okibank {

class cache_iterator {
  private_user *current;

public:
  explicit cache_iterator(private_user *curr);

  constexpr inline private_user *get_current() const noexcept;

  constexpr inline private_user &operator*() const noexcept;

  constexpr inline cache_iterator &operator++() noexcept;

  constexpr inline cache_iterator &operator--() noexcept;

  unsigned short operator-(cache_iterator &&second) noexcept;

  constexpr inline bool operator==(const cache_iterator &other) const noexcept;

  constexpr inline bool operator!=(const cache_iterator &other) const noexcept;

  constexpr inline private_user *operator->() noexcept;
};

} // namespace okibank

#endif
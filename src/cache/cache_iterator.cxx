#include "cache_iterator.hxx"

namespace okibank {

template <is_oki_iterator It>
constexpr inline It &operator++(It &val) noexcept {
  ++val.current;
  return val;
}

template <is_oki_iterator It>
constexpr inline It operator++(It &val, int) noexcept {
  It temp(val);
  ++val;
  return temp;
}

template <is_oki_iterator It>
constexpr inline It &operator--(It &val) noexcept {
  --val.current;
  return val;
}

template <is_oki_iterator It>
constexpr inline It operator--(It &val, int) noexcept {
  It temp(val);
  ++val;
  return temp;
};

template <is_oki_iterator It>
int16_t operator-(const It &val1, const It &&val2) noexcept {
  return val1.current - val2.current;
}

template <is_oki_iterator It>
bool operator==(const It &val1, const It &val2) noexcept {
  return val1.current == val2.current;
}

template <is_oki_iterator It>
bool operator!=(const It &val1, const It &val2) noexcept {
  return val1.current != val2.current;
}

cache_iterator::cache_iterator(cache_iterator::pointer curr) : current(curr) {
}

constexpr inline cache_iterator::pointer cache_iterator::operator->() noexcept {
  return current;
}

const_cache_iterator::const_cache_iterator(const_cache_iterator::pointer curr)
    : current(curr) {
}

template <is_oki_iterator It> It::reference operator*(It &val) noexcept {
  return *val.current;
}

constexpr inline const_cache_iterator::pointer
const_cache_iterator::operator->() noexcept {
  return current;
}

template cache_iterator &operator++(cache_iterator &val) noexcept;

template cache_iterator operator++(cache_iterator &val, int) noexcept;

template cache_iterator &operator--(cache_iterator &val) noexcept;

template cache_iterator operator--(cache_iterator &val, int) noexcept;

template int16_t operator-(const cache_iterator &val1,
                           const cache_iterator &&val2) noexcept;

template bool operator==(const cache_iterator &val1,
                         const cache_iterator &val2) noexcept;

template bool operator!=(const cache_iterator &val1,
                         const cache_iterator &val2) noexcept;

template const_cache_iterator &operator++(const_cache_iterator &val) noexcept;

template const_cache_iterator operator++(const_cache_iterator &val,
                                         int) noexcept;

template const_cache_iterator &operator--(const_cache_iterator &val) noexcept;

template const_cache_iterator operator--(const_cache_iterator &val,
                                         int) noexcept;

template int16_t operator-(const const_cache_iterator &val1,
                           const const_cache_iterator &&val2) noexcept;

template bool operator==(const const_cache_iterator &val1,
                         const const_cache_iterator &val2) noexcept;

template bool operator!=(const const_cache_iterator &val1,
                         const const_cache_iterator &val2) noexcept;

template private_user &operator*(cache_iterator &obj) noexcept;

template const private_user &operator*(const_cache_iterator &obj) noexcept;

} // namespace okibank
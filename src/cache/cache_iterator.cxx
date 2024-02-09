#include "cache_iterator.hxx"

namespace okibank {

cache_iterator::cache_iterator(private_user *curr) : current(curr) {
}

constexpr inline private_user *cache_iterator::get_current() const noexcept {
  return current;
}

constexpr inline private_user &cache_iterator::operator*() const noexcept {
  return *current;
}

constexpr inline cache_iterator &cache_iterator::operator++() noexcept {
  ++current;
  return *this;
}

constexpr inline cache_iterator &cache_iterator::operator--() noexcept {
  --current;
  return *this;
}

unsigned short cache_iterator::operator-(cache_iterator &&second) noexcept {
  return this->current - second.current;
}

constexpr inline bool
cache_iterator::operator==(const cache_iterator &other) const noexcept {
  return current == other.current;
}

constexpr inline bool
cache_iterator::operator!=(const cache_iterator &other) const noexcept {
  return !(*this == other);
}

constexpr inline private_user *cache_iterator::operator->() noexcept {
  return current;
}

} // namespace okibank
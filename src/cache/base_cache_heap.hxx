#ifndef CACHE_BASE_CACHE_HEAP_HXX
#define CACHE_BASE_CACHE_HEAP_HXX

#include "../models/private_user.hxx"
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <malloc.h>

namespace okibank {

using heap_size = uint16_t;
using heap_pos = heap_size;
using byte = char;

template <heap_size size> class cache_controller;

template <heap_size size> class base_cache_heap {
private:
  byte *cache;
  std::atomic<heap_pos> __last_pos;
  std::atomic<heap_pos> __end;
  std::atomic<bool> __full;

  constexpr inline size_t obj_size() {
    return sizeof(private_user);
  }

  heap_pos next_pos() {
    heap_pos ppos = __last_pos + obj_size();

    if (ppos > size - obj_size()) {
      ppos = 0;
    }

    __last_pos = ppos;
    return ppos;
  }

  constexpr inline void reset() noexcept {
    __last_pos = 0;
  }

public:
  base_cache_heap()
      : __last_pos(0), __end(0), cache(new byte[size * obj_size()]) {
  }

  ~base_cache_heap() {
    delete[] cache;
  }

  constexpr inline const private_user &insert(const private_user &tr) {
    return std::memmove(cache[next_pos()], &tr, obj_size());
  }

  class cache_iterator {
    private_user *current;

  public:
    explicit cache_iterator(private_user *curr) : current(curr) {
    }

    constexpr inline private_user *get_current() const noexcept {
      return current;
    }

    constexpr inline private_user &operator*() const noexcept {
      return *current;
    }

    constexpr inline cache_iterator &operator++() noexcept {
      ++current;
      return *this;
    }

    constexpr inline cache_iterator &operator--() noexcept {
      --current;
      return *this;
    }

    constexpr inline cache_iterator *
    operator+(const cache_iterator &second) noexcept {
      return cache_iterator(this->current + second.current);
    }

    constexpr inline cache_iterator *
    operator-(const cache_iterator &second) noexcept {
      return cache_iterator(this->current - second.current);
    }

    constexpr inline bool
    operator==(const cache_iterator &other) const noexcept {
      return current == other.current;
    }

    constexpr inline bool
    operator!=(const cache_iterator &other) const noexcept {
      return !(*this == other);
    }

    constexpr inline private_user *operator->() noexcept {
      return current;
    }
  };

  void rewrite(cache_iterator place, const private_user &val) noexcept {
    int s_last_pos = __last_pos;
    __last_pos = (place - begin()).get_current();
    insert(val);
    __last_pos = s_last_pos;
  }

  constexpr inline cache_iterator begin() noexcept {
    return cache_iterator(reinterpret_cast<private_user *>(cache));
  }

  cache_iterator end() noexcept {
    if (__full) {
      return cache_iterator(reinterpret_cast<private_user *>(cache) + size);
    }

    return cache_iterator(reinterpret_cast<private_user *>(cache) + __last_pos);
  }

  friend class cache_controller<size>;
};

} // namespace okibank

#endif
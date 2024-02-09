#ifndef CACHE_BASE_CACHE_HEAP_HXX
#define CACHE_BASE_CACHE_HEAP_HXX

#include "cache_iterator.hxx"
#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <malloc.h>

namespace okibank {

using heap_size = uint16_t;
using heap_pos = heap_size;
using byte = char;

template <class T, heap_size size> class cache_controller;

template <class T, heap_size size> class base_cache_heap {
private:
  byte *cache;
  std::atomic<heap_pos> __last_pos;
  std::atomic<heap_pos> __end;
  std::atomic<bool> __full;

  constexpr inline size_t obj_size() noexcept;
  heap_pos next_pos() noexcept;
  constexpr inline void reset() noexcept;

public:
  base_cache_heap();
  ~base_cache_heap();

  constexpr inline const T &insert(const T &tr);

  void rewrite(cache_iterator place, const T &val) noexcept;

  inline cache_iterator begin() noexcept;

  cache_iterator end() noexcept;

  friend class cache_controller<T, size>;
};

} // namespace okibank

#endif
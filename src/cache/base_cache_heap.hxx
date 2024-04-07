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
using byte = uint8_t;

template <class T, heap_size size> class cache_controller;

template <class T, heap_size size> class base_cache_heap {
private:
  byte *cache;
  std::atomic<heap_pos> __last_pos;
  std::atomic<heap_pos> __end;
  std::atomic<bool> __full;

  constexpr inline size_t obj_size() noexcept {
    return sizeof(T);
  }

  heap_pos next_pos() noexcept {
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

  template <std::input_or_output_iterator It, class InnT> It iterator_begin() {
    return It(reinterpret_cast<InnT>(cache));
  }

  template <std::input_or_output_iterator It, class InnT> It iterator_end() {
    if (__full) {
      return It(reinterpret_cast<InnT>(cache) + size);
    }

    return It(reinterpret_cast<InnT>(cache + __last_pos));
  }

public:
  base_cache_heap()
      : cache(new byte[size * obj_size()]), __last_pos(0), __end(0) {
  }

  ~base_cache_heap() {
    delete[] cache;
  }

  constexpr inline const T &insert(const T &tr) {
    return *reinterpret_cast<T *>(
        std::memmove(&cache[next_pos()], &tr, obj_size()));
  }

  void rewrite(cache_iterator place, const T &val) noexcept {
    int s_last_pos = __last_pos;
    __last_pos = place - begin();
    insert(val);
    __last_pos = s_last_pos;
  }

  inline cache_iterator begin() noexcept {
    return iterator_begin<cache_iterator, private_user *>();
  }

  cache_iterator end() noexcept {
    return iterator_end<cache_iterator, private_user *>();
  }

  inline const_cache_iterator cbegin() noexcept {
    return iterator_begin<const_cache_iterator, const private_user *>();
  }

  const_cache_iterator cend() noexcept {
    return iterator_end<const_cache_iterator, const private_user *>();
  }

  constexpr inline bool operator==(base_cache_heap<T, size> &other) {
    return this->cache == other.cache;
  }

  constexpr inline bool operator!=(base_cache_heap<T, size> &other) {
    return this->cache != other.cache;
  }

  inline bool empty() {
    return begin() == end();
  }

  friend class cache_controller<T, size>;
};

} // namespace okibank

#endif
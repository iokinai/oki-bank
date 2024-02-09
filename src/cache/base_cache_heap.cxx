#include "base_cache_heap.hxx"
#include "cache_iterator.hxx"

namespace okibank {

template <class T, heap_size size>
constexpr inline size_t base_cache_heap<T, size>::obj_size() noexcept {
  return sizeof(T);
}

template <class T, heap_size size>
heap_pos base_cache_heap<T, size>::next_pos() noexcept {
  heap_pos ppos = __last_pos + obj_size();

  if (ppos > size - obj_size()) {
    ppos = 0;
  }

  __last_pos = ppos;
  return ppos;
}

template <class T, heap_size size>
constexpr inline void base_cache_heap<T, size>::reset() noexcept {
  __last_pos = 0;
}

template <class T, heap_size size>
base_cache_heap<T, size>::base_cache_heap()
    : cache(new byte[size * obj_size()]), __last_pos(0), __end(0) {
}

template <class T, heap_size size>
base_cache_heap<T, size>::~base_cache_heap() {
  delete[] cache;
}

template <class T, heap_size size>
constexpr inline const T &base_cache_heap<T, size>::insert(const T &tr) {
  return *reinterpret_cast<T *>(
      std::memmove(&cache[next_pos()], &tr, obj_size()));
}

template <class T, heap_size size>
void base_cache_heap<T, size>::rewrite(cache_iterator place,
                                       const T &val) noexcept {
  int s_last_pos = __last_pos;
  __last_pos = place - begin();
  insert(val);
  __last_pos = s_last_pos;
}

template <class T, heap_size size>
inline cache_iterator base_cache_heap<T, size>::begin() noexcept {
  return cache_iterator(reinterpret_cast<T *>(cache));
}

template <class T, heap_size size>
cache_iterator base_cache_heap<T, size>::end() noexcept {
  if (__full) {
    return cache_iterator(reinterpret_cast<T *>(cache) + size);
  }

  return cache_iterator(reinterpret_cast<T *>(cache) + __last_pos);
}

template class base_cache_heap<private_user, 1024>;

} // namespace okibank
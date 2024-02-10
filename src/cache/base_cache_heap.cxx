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
template <std::input_or_output_iterator It, class InnT>
It base_cache_heap<T, size>::iterator_begin() {
  return It(reinterpret_cast<InnT>(cache));
}

template <class T, heap_size size>
template <std::input_or_output_iterator It, class InnT>
It base_cache_heap<T, size>::iterator_end() {
  if (__full) {
    return It(reinterpret_cast<InnT>(cache) + size);
  }

  return It(reinterpret_cast<InnT>(cache + __last_pos));
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
  return iterator_begin<cache_iterator, private_user *>();
}

template <class T, heap_size size>
cache_iterator base_cache_heap<T, size>::end() noexcept {
  return iterator_end<cache_iterator, private_user *>();
}

template <class T, heap_size size>
inline const_cache_iterator base_cache_heap<T, size>::cbegin() noexcept {
  return iterator_begin<const_cache_iterator, const private_user *>();
}

template <class T, heap_size size>
const_cache_iterator base_cache_heap<T, size>::cend() noexcept {
  return iterator_end<const_cache_iterator, const private_user *>();
}

template <class T, heap_size size>
constexpr inline bool
base_cache_heap<T, size>::operator==(base_cache_heap<T, size> &other) {
  return this->cache == other.cache;
}

template <class T, heap_size size>
constexpr inline bool
base_cache_heap<T, size>::operator!=(base_cache_heap<T, size> &other) {
  return this->cache != other.cache;
}

template <class T, heap_size size>
inline bool base_cache_heap<T, size>::empty() {
  return begin() == end();
}

template class base_cache_heap<private_user, 1024>;

} // namespace okibank
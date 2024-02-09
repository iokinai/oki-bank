#include "cache_controller.hxx"
#include "base_cache_heap.hxx"

namespace okibank {

template <class T, heap_size size>
cache_controller<T, size>::cache_controller(
    const base_cache_heap<T, size> &heap)
    : heap(heap) {
}

template <class T, heap_size size>
void cache_controller<T, size>::reset_heap() noexcept {
  heap.reset();
}

} // namespace okibank
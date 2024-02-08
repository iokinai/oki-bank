#ifndef CACHE_CACHE_CONTROLLER_HXX
#define CACHE_CACHE_CONTROLLER_HXX

#include "base_cache_heap.hxx"

namespace okibank {

template <heap_size size> class cache_controller {
protected:
  base_cache_heap<size> heap;

public:
  cache_controller<size>(const base_cache_heap<size> &heap) : heap(heap) {
  }

  virtual bool is_in_cache(public_account_info &cn,
                           private_account_info &cvc) const noexcept = 0;

  virtual bool
  insert(std::pair<private_user, private_user> &&users) noexcept = 0;

  void reset_heap() noexcept {
    heap.reset();
  }
};

} // namespace okibank

#endif
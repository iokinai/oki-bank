#ifndef CACHE_STD_CACHE_CONTROLLER_HXX
#define CACHE_STD_CACHE_CONTROLLER_HXX

#include "base_cache_heap.hxx"
#include "cache_controller.hxx"

namespace okibank {

template <class T, heap_size size>
class std_cache_controller : public cache_controller<T, size> {

private:
  void insert_or_rewrite(const private_user &user);

public:
  std_cache_controller();

  std_cache_controller(const base_cache_heap<T, size> &heap);

  cache_iterator find_in_cache(public_account_info &cn,
                               private_account_info &cvc);

  virtual bool is_in_cache(public_account_info &cn,
                           private_account_info &cvc) const noexcept;

  virtual bool
  insert(std::pair<const private_user &, const private_user &> users) noexcept;

  constexpr inline std_cache_controller(const std_cache_controller &other);

  constexpr inline std_cache_controller(std_cache_controller &&other);
};

} // namespace okibank

#endif
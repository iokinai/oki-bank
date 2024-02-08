#ifndef CACHE_STD_CACHE_CONTROLLER_HXX
#define CACHE_STD_CACHE_CONTROLLER_HXX

#include "base_cache_heap.hxx"
#include "cache_controller.hxx"
#include <algorithm>

namespace okibank {

template <heap_size size>
class std_cache_controller : public cache_controller<size> {

  using cache_iterator = base_cache_heap<size>::cache_iterator;

private:
  void insert_or_rewrite(const private_user &user) {
    cache_iterator pos = find_in_cache(user.get_public_account_info(),
                                       user.get_private_account_info());

    if (pos == this->heap.end()) {
      this->heap.insert(user);
      return;
    }

    this->heap.rewrite(pos, user);
  }

public:
  std_cache_controller() : cache_controller<size>(base_cache_heap<size>()) {
  }

  std_cache_controller(const base_cache_heap<size> &heap)
      : cache_controller<size>(heap) {
  }

  cache_iterator find_in_cache(public_account_info &cn,
                               private_account_info &cvc) {
    return std::find_if(
        this->heap.begin(), this->heap.end(),
        [&](const private_user &us) -> bool {
          return us.get_private_account_info().get_cvc() == cvc.get_cvc() &&
                 us.get_public_account_info().get_card_number() ==
                     cn.get_card_number();
        });
  }

  virtual bool is_in_cache(public_account_info &cn,
                           private_account_info &cvc) const noexcept {
    return find_in_cache(cn, cvc) != this->heap.end();
  }

  virtual bool
  insert(std::pair<const private_user &, const private_user &> users) noexcept {
    insert_or_rewrite(users.first);
    insert_or_rewrite(users.second);
  }

  constexpr inline std_cache_controller(const std_cache_controller &other) {
    this->heap = other.heap;
  }

  constexpr inline std_cache_controller(std_cache_controller &&other) {
    this->heap = std::move(other.heap);
  }
};

} // namespace okibank

#endif
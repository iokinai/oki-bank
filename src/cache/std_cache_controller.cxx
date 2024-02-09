#include "std_cache_controller.hxx"
#include "base_cache_heap.hxx"

namespace okibank {

template <class T, heap_size size>
void std_cache_controller<T, size>::insert_or_rewrite(
    const private_user &user) {
  cache_iterator pos = find_in_cache(user.get_public_account_info(),
                                     user.get_private_account_info());

  if (pos == this->heap.end()) {
    this->heap.insert(user);
    return;
  }

  this->heap.rewrite(pos, user);
}

template <class T, heap_size size>
std_cache_controller<T, size>::std_cache_controller()
    : cache_controller<T, size>(base_cache_heap<T, size>()) {
}

template <class T, heap_size size>
std_cache_controller<T, size>::std_cache_controller(
    const base_cache_heap<T, size> &heap)
    : cache_controller<T, size>(heap) {
}

template <class T, heap_size size>
cache_iterator
std_cache_controller<T, size>::find_in_cache(public_account_info &cn,
                                             private_account_info &cvc) {
  return std::find_if(this->heap.begin(), this->heap.end(),
                      [&](const private_user &us) -> bool {
                        return us.get_private_account_info().get_cvc() ==
                                   cvc.get_cvc() &&
                               us.get_public_account_info().get_card_number() ==
                                   cn.get_card_number();
                      });
}

template <class T, heap_size size>
bool std_cache_controller<T, size>::is_in_cache(
    public_account_info &cn, private_account_info &cvc) const noexcept {
  return find_in_cache(cn, cvc) != this->heap.end();
}

template <class T, heap_size size>
bool std_cache_controller<T, size>::insert(
    std::pair<const private_user &, const private_user &> users) noexcept {
  insert_or_rewrite(users.first);
  insert_or_rewrite(users.second);
}

template <class T, heap_size size>
constexpr inline std_cache_controller<T, size>::std_cache_controller(
    const std_cache_controller &other) {
  this->heap = other.heap;
}

template <class T, heap_size size>
constexpr inline std_cache_controller<T, size>::std_cache_controller(
    std_cache_controller &&other) {
  this->heap = std::move(other.heap);
}

} // namespace okibank
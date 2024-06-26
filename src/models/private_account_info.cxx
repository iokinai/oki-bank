#include "private_account_info.hxx"

#include <utility>

namespace okibank {
private_account_info::private_account_info(uint8_t cvc) : cvc(cvc) {
}

private_account_info::private_account_info(const private_account_info &acc)
    : cvc(acc.get_cvc()) {
}

private_account_info::private_account_info(private_account_info &&acc)
    : cvc(std::move(acc.get_cvc())) {
}
} // namespace okibank
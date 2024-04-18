#include "public_account_info.hxx"

namespace okibank {
public_account_info::public_account_info(const std::string &card_number)
    : card_number(card_number) {
}

public_account_info::public_account_info(const public_account_info &acc)
    : card_number(acc.get_card_number()) {
}

public_account_info::public_account_info(public_account_info &&acc)
    : card_number(std::move(acc.get_card_number())) {
}

} // namespace okibank
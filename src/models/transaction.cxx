#include "transaction.hxx"
#include "public_account_info.hxx"

namespace okibank {

transaction::transaction(const private_account_info &from,
                         const public_account_info &to,
                         const long double amount)
    : from(from), to(to), amount(amount) {
}

transaction::transaction(const transaction &tr)
    : from(tr.get_from()), to(tr.get_to()), amount(tr.get_amount()) {
}

transaction::transaction(transaction &&tr)
    : from(std::move(tr.get_from())), to(std::move(tr.get_to())),
      amount(std::move(tr.get_amount())) {
}

} // namespace okibank
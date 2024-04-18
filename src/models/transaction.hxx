#ifndef MODELS_TRANSACTION_HXX
#define MODELS_TRANSACTION_HXX

#include "private_account_info.hxx"
#include "public_account_info.hxx"

namespace okibank {

class SHARED_EXPORT transaction final {
private:
  const private_account_info &from;
  const public_account_info &to;
  const long double amount;

public:
  transaction(const private_account_info &from, const public_account_info &to,
              const long double amount);
  transaction(const transaction &);
  transaction(transaction &&);

  constexpr inline const private_account_info &get_from(void) const noexcept {
    return this->from;
  }

  constexpr inline const public_account_info &get_to(void) const noexcept {
    return this->to;
  }

  constexpr inline const long double get_amount(void) const noexcept {
    return this->amount;
  }
};

} // namespace okibank

#endif
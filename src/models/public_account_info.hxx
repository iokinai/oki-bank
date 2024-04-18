#ifndef MODELS_PUBLIC_ACCOUNT_INFO
#define MODELS_PUBLIC_ACCOUNT_INFO

#include <cfg.hxx>
#include <string>

namespace okibank {

class SHARED_EXPORT public_account_info {
private:
  std::string card_number;

public:
  public_account_info(const std::string &card_number);
  public_account_info(const public_account_info &acc);
  public_account_info(public_account_info &&);

  constexpr inline const std::string &get_card_number(void) const noexcept {
    return this->card_number;
  }
};

} // namespace okibank

#endif
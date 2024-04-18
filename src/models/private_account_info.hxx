#ifndef MODELS_PRIVATE_ACCOUNT_INFO_HXX
#define MODELS_PRIVATE_ACCOUNT_INFO_HXX

#include <cfg.hxx>
#include <cstdint>

namespace okibank {

class SHARED_EXPORT private_account_info {
private:
  uint8_t cvc;

public:
  private_account_info(uint8_t cvc);
  private_account_info(const private_account_info &acc);
  private_account_info(private_account_info &&acc);

  constexpr inline uint8_t get_cvc(void) const noexcept {
    return this->cvc;
  }
};

} // namespace okibank

#endif
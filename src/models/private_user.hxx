#ifndef MODELS_PRIVATE_USER_HXX
#define MODELS_PRIVATE_USER_HXX

#include "private_account_info.hxx"
#include "public_user.hxx"
#include "transaction.hxx"
#include <cstdint>
#include <vector>

namespace okibank {

class SHARED_EXPORT private_user : public public_user {
private:
  private_account_info priv_acc_info;
  std::vector<uint8_t> password_hash;
  std::string secret_word;
  std::vector<transaction> transactions;

public:
  private_user(std::string card_number, uint8_t cvc, std::string user_name,
               std::string user_description, user_status status,
               date registred_at, date last_online,
               std::vector<uint8_t> password_hash, std::string secret_word,
               std::vector<transaction> transactions);

  private_user(const public_user &pubuser, uint8_t cvc,
               std::vector<uint8_t> password_hash, std::string secret_word,
               std::vector<transaction> transactions);

  private_user(const private_user &us);

  private_user(private_user &&us);

  const private_account_info &get_private_account_info(void) const noexcept;
  const std::vector<uint8_t> &get_password_hash(void) const noexcept;
  const std::string &get_secret_word(void) const noexcept;
  const std::vector<transaction> &get_transactions(void) const noexcept;
};

} // namespace okibank

#endif
#include "private_user.hxx"
#include "public_user.hxx"
#include "transaction.hxx"

namespace okibank {

private_user::private_user(const public_user &pubuser, uint8_t cvc,
                           std::vector<uint8_t> password_hash,
                           std::string secret_word,
                           std::vector<transaction> transactions)
    : public_user(pubuser), priv_acc_info(cvc), password_hash(password_hash),
      secret_word(secret_word), transactions(transactions) {
}

private_user::private_user(std::string card_number, uint8_t cvc,
                           std::string user_name, std::string user_description,
                           user_status status, date registred_at,
                           date last_online, std::vector<uint8_t> password_hash,
                           std::string secret_word,
                           std::vector<transaction> transactions)
    : private_user(public_user(card_number, user_name, user_description, status,
                               registred_at, last_online),
                   cvc, password_hash, secret_word, transactions) {
}

private_user::private_user(const private_user &us)
    : public_user(us.get_public_account_info().get_card_number(),
                  us.get_user_name(), us.get_user_description(),
                  us.get_status(), us.get_registred_at(), us.get_last_online()),
      priv_acc_info(us.get_private_account_info()),
      password_hash(us.get_password_hash()), secret_word(us.get_secret_word()),
      transactions(us.get_transactions()) {
}

private_user::private_user(private_user &&us)
    : public_user(std::move(us.get_public_account_info().get_card_number()),
                  std::move(us.get_user_name()),
                  std::move(us.get_user_description()),
                  std::move(us.get_status()), std::move(us.get_registred_at()),
                  std::move(us.get_last_online())),
      priv_acc_info(std::move(us.get_private_account_info())),
      password_hash(std::move(us.get_password_hash())),
      secret_word(std::move(us.get_secret_word())),
      transactions(std::move(us.get_transactions())) {
}

} // namespace okibank
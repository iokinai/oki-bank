#include "public_user.hxx"
#include "public_account_info.hxx"

namespace okibank {
public_user::public_user(std::string card_number, std::string user_name,
                         std::string user_description, user_status status,
                         date registred_at, date last_online)
    : pub_acc_info(card_number), user_name(user_name),
      user_description(user_description), status(status),
      registred_at(registred_at), last_online(last_online) {
}

public_user::public_user(const public_user &user)
    : pub_acc_info(user.get_public_account_info()),
      user_name(user.get_user_name()),
      user_description(user.get_user_description()), status(user.get_status()),
      registred_at(user.get_registred_at()),
      last_online(user.get_last_online()) {
}

public_user::public_user(public_user &&user)
    : pub_acc_info(std::move(user.get_public_account_info())),
      user_name(std::move(user.get_user_name())),
      user_description(std::move(user.get_user_description())),
      status(std::move(user.get_status())),
      registred_at(std::move(user.get_registred_at())),
      last_online(std::move(user.get_last_online())) {
}

const std::string &public_user::get_user_name(void) const noexcept {
  return this->user_name;
}

const std::string &public_user::get_user_description(void) const noexcept {
  return this->user_description;
}

user_status public_user::get_status(void) const noexcept {
  return this->status;
}

const date &public_user::get_registred_at(void) const noexcept {
  return this->registred_at;
}

const date &public_user::get_last_online(void) const noexcept {
  return this->last_online;
}

const public_account_info &
public_user::get_public_account_info(void) const noexcept {
  return this->pub_acc_info;
}

} // namespace okibank
#ifndef MODELS_PUBLIC_USER_HXX
#define MODELS_PUBLIC_USER_HXX

#include "public_account_info.hxx"
#include "user_status.hxx"
#include <chrono>
#include <string>

namespace okibank {

using date = std::chrono::time_point<std::chrono::steady_clock>;

class SHARED_EXPORT public_user {
private:
  public_account_info pub_acc_info;
  std::string user_name;
  std::string user_description;
  user_status status;
  date registred_at;
  date last_online;

public:
  public_user(std::string card_number, std::string user_name,
              std::string user_description, user_status status,
              date registred_at, date last_online);

  public_user(const public_user &user);

  public_user(public_user &&user);

  constexpr inline const std::string &get_user_name(void) const noexcept {
    return this->user_name;
  }

  constexpr inline const std::string &
  get_user_description(void) const noexcept {
    return this->user_description;
  }

  constexpr inline user_status get_status(void) const noexcept {
    return this->status;
  }

  constexpr inline const date &get_registred_at(void) const noexcept {
    return this->registred_at;
  }

  constexpr inline const date &get_last_online(void) const noexcept {
    return this->last_online;
  }

  constexpr inline const public_account_info &
  get_public_account_info(void) const noexcept {
    return this->pub_acc_info;
  }
};

} // namespace okibank

#endif
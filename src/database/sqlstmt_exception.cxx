#include "sqlstmt_exception.hxx"

namespace okibank {

sqlstmt_exception::sqlstmt_exception(const std::string &reason)
    : reason(reason) {}

const char *sqlstmt_exception::what() const noexcept {
  return this->reason.c_str();
}

} // namespace okibank
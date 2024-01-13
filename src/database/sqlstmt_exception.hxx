#ifndef DATABASE_SQLSTMT_EXCEPTION_HXX
#define DATABASE_SQLSTMT_EXCEPTION_HXX

#include <cfg.hxx>
#include <exception>
#include <string>

namespace okibank {

class SHARED_EXPORT sqlstmt_exception : public std::exception {
private:
  std::string reason;

public:
  sqlstmt_exception(const std::string &reason);

  const char *what() const noexcept override;
};

} // namespace okibank

#endif
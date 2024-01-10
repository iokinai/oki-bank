#ifndef DATABASE_SQLITE_EXCEPTIONS_SQLITE_EXCEPTION_HXX
#define DATABASE_SQLITE_EXCEPTIONS_SQLITE_EXCEPTION_HXX

#include <cfg.hxx>
#include <exception>
#include <string>

namespace okibank {

class SHARED_EXPORT sqlite_exception : public std::exception {
private:
  std::string error_text = "An sqlite3 error occured: ";

public:
  sqlite_exception(int error);
  const char *what() const noexcept override;
};

} // namespace okibank

#endif
#ifndef DATABASE_SQLSTMT_HXX
#define DATABASE_SQLSTMT_HXX

#include "sqlsettings.hxx"
#include <cfg.hxx>
#include <string>

namespace okibank {

class SHARED_EXPORT sqlstmt {
protected:
  sqlinnerstmt **stmt;

  virtual void do_bind(int pos, int value) = 0;
  virtual void do_bind(int pos, double value) = 0;
  virtual void do_bind(int pos, const std::string &value) = 0;
  virtual void do_bind(int pos) = 0;

public:
  sqlstmt(sqlinnerstmt **stmt);

  template <class T> void bind(int pos, T value);

  sqlinnerstmt **get_stmt(void) const noexcept;

  virtual ~sqlstmt() = default;
};

} // namespace okibank

#endif
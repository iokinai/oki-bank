#ifndef DATABASE_SQLITE_SQLITE3_RSTMT_HXX
#define DATABASE_SQLITE_SQLITE3_RSTMT_HXX

#include "../sqlstmt.hxx"
#include <cfg.hxx>

namespace okibank {

struct SHARED_EXPORT sqlite3_rstmt : public sqlstmt {
  sqlite3_rstmt(sqlite3_stmt **stmt);

  void do_bind(int pos, int value) override;
  void do_bind(int pos, double value) override;
  void do_bind(int pos, const std::string &value) override;
  void do_bind(int pos) override;

  ~sqlite3_rstmt() override;
};

} // namespace okibank

#endif
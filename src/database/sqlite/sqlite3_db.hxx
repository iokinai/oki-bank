#ifndef DATABASE_SQLITE_SQLITE3_DB_HXX
#define DATABASE_SQLITE_SQLITE3_DB_HXX

#include "../sqldb.hxx"
#include <cfg.hxx>

namespace okibank {

class SHARED_EXPORT sqlite3_db : public sqldb {
public:
  sqlite3_db(const std::string &path);
  ~sqlite3_db() override;
  void prepare(const std::string &stmt, sqlstmt &rstmt) override;
  void send(const sqlstmt &stmt) override;
  query_result_ref result(const sqlstmt &stmt) override;
  query_result_ref exec(const std::string &stmt) override;
};

} // namespace okibank

#endif
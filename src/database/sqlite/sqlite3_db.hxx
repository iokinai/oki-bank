#ifndef DATABASE_SQLITE_SQLITE3_DB_HXX
#define DATABASE_SQLITE_SQLITE3_DB_HXX

#include "../sqldb.hxx"
#include <cfg.hxx>

namespace okibank {

class SHARED_EXPORT sqlite3_db : public sqldb {
private:
  std::string path;

public:
  sqlite3_db(const std::string &path);
  ~sqlite3_db() override;
  void prepare(const std::string &stmt, sqlstmt &rstmt) override;
  void send(const sqlstmt &stmt) override;
  std::shared_ptr<std::unordered_map<std::string, std::string>>
  result(const sqlstmt &stmt) override;
};

} // namespace okibank

#endif
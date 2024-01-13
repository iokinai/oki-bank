#include "sqlite3_db.hxx"
#include "exceptions/sqlite_exception.hxx"
#include "sqlite3_rstmt.hxx"
#include <string>
#include <unordered_map>

namespace okibank {

sqlite3_db::sqlite3_db(const std::string &path) : path(path) {
  sqlite3 **db = nullptr;

  int res = sqlite3_open(this->path.c_str(), db);

  if (res != 0) {
    throw sqlite_exception(res);
  }

  this->connection = db;
}

sqlite3_db::~sqlite3_db() { sqlite3_close(*this->connection); }

void sqlite3_db::prepare(const std::string &stmt, sqlstmt &rstmt) {
  sqlite3_stmt **statement = nullptr;

  int res = sqlite3_prepare_v2(*this->connection, stmt.c_str(),
                               sizeof(stmt.c_str()), statement, nullptr);

  if (res != 0) {
    throw sqlite_exception(res);
  }

  rstmt = sqlite3_rstmt(statement);
}

void sqlite3_db::send(const sqlstmt &stmt) {
  int res;

  do {
    res = sqlite3_step(*stmt.get_stmt());
  } while (res == SQLITE_BUSY);

  if (res != 0) {
    throw sqlite_exception(res);
  }
}

std::shared_ptr<std::unordered_map<std::string, std::string>>
sqlite3_db::result(const sqlstmt &stmt) {
  std::shared_ptr<std::unordered_map<std::string, std::string>> result =
      std::make_shared<std::unordered_map<std::string, std::string>>();

  int columns_count = sqlite3_data_count(*stmt.get_stmt());

  if (columns_count == 0) {
    throw -1; // TODO: override
  }

  for (int i{0}; i < columns_count; i++) {
    std::string column_name = sqlite3_column_name(*stmt.get_stmt(), i);
    std::string value = reinterpret_cast<const char *>(
        sqlite3_column_text(*stmt.get_stmt(), i));
    result->insert({column_name, value});
  }

  return result;
}

} // namespace okibank
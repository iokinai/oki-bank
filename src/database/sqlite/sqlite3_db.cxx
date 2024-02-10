#include "sqlite3_db.hxx"
#include "exceptions/sqlite_exception.hxx"
#include "sqlite3.h"
#include <cstddef>
#include <memory>
#include <string>
#include <unordered_map>

namespace okibank {

sqlite3_db::sqlite3_db(const std::string &path) : sqldb(path) {
  sqlite3 *db;

  int res = sqlite3_open(this->path.c_str(), &db);

  if (res != 0) {
    throw sqlite_exception(res);
  }

  this->connection = db;
}

sqlite3_db::~sqlite3_db() {
  sqlite3_close(this->connection);
}

void sqlite3_db::prepare(const std::string &stmt, sqlstmt &rstmt) {
  sqlite3_stmt *statement = nullptr;

  int res = sqlite3_prepare_v2(this->connection, stmt.c_str(), -1, &statement,
                               nullptr);

  if (res != 0) {
    throw sqlite_exception(res);
  }

  rstmt.set_stmt(statement);
}

void sqlite3_db::send(const sqlstmt &stmt) {
  int res;

  do {
    res = sqlite3_step(stmt.get_stmt());
  } while (res == SQLITE_BUSY);

  if (res != SQLITE_DONE) {
    throw sqlite_exception(res);
  }
}

query_result_ref sqlite3_db::result(const sqlstmt &stmt) {
  query_result_ref result = std::make_shared<query_result>();

  int columns_count = sqlite3_data_count(stmt.get_stmt());

  if (columns_count == 0) {
    throw -1; // TODO: override
  }

  for (int i{0}; i < columns_count; i++) {
    std::string column_name = sqlite3_column_name(stmt.get_stmt(), i);
    std::string value =
        reinterpret_cast<const char *>(sqlite3_column_text(stmt.get_stmt(), i));
    result->insert({column_name, value});
  }

  return result;
}

std::shared_ptr<query_result> sqlite3_db::exec(const std::string &stmt) {
  query_result *result = new query_result;

  char *err_msg = nullptr;

  int exec_res = sqlite3_exec(
      this->connection, stmt.c_str(),
      [](void *r, int cons, char **names, char **values) -> int {
        auto res = static_cast<query_result *>(r);

        for (size_t i = 0; i < sizeof(**names); i++) {
          std::string name = names[i];
          (*res)[name] = values[i];
        }

        return 0;
      },
      result, &err_msg);

  if (exec_res != 0) {
    throw -1; // TODO: override
  }

  sqlite3_free(err_msg);

  return std::shared_ptr<query_result>(result);
}

} // namespace okibank
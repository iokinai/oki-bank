#include "app_init.hxx"
#include "database/sqlite/sqlite3_db.hxx"

namespace okibank::app {

template <sql_database T> T open_db(const std::string &path) {
  return sqlite3_db(path);
}

template <sql_database T> void init_db(const T &database) {}

} // namespace okibank::app
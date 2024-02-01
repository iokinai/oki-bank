#ifndef APP_INIT_HXX
#define APP_INIT_HXX

#include "concepts.hxx"
#include "database/sqlite/sqlite3_db.hxx"
#include "database/sqlite/sqlite3_rstmt.hxx"
#include <memory>
#include <string>

namespace okibank::app {

template <sql_database T> T open_db(const std::string &path) { return T(path); }

template <sql_database T> void init_db(T &database) {
  std::string expr = "CREATE TABLE IF NOT EXISTS Users (      \
    id INTEGER PRIMARY KEY AUTOINCREMENT,                     \
    user_name TEXT,                                           \
    password_hash TEXT,                                       \
    user_description TEXT,                                    \
    status INTEGER,                                           \
    registed_at INTEGER,                                      \
    last_online INTEGER,                                      \
    cvc INTEGER,                                              \
    card_number TEXT,                                         \
    secret_word TEXT                                          \
  )";

  sqlite3_rstmt stmt(nullptr);

  database.prepare(expr, stmt);
  database.send(stmt);
}

} // namespace okibank::app

#endif
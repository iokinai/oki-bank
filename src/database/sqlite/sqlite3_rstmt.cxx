#include "sqlite3_rstmt.hxx"
#include <sqlite3.h>

namespace okibank {

sqlite3_rstmt::sqlite3_rstmt(sqlite3_stmt **stmt) : sqlstmt(stmt) {}

void sqlite3_rstmt::do_bind(int pos, int value) {
  sqlite3_bind_int(*this->stmt, pos, value);
}

void sqlite3_rstmt::do_bind(int pos, double value) {
  sqlite3_bind_double(*this->stmt, pos, value);
}

void sqlite3_rstmt::do_bind(int pos, const std::string &value) {
  sqlite3_bind_text(*this->stmt, pos, value.c_str(), sizeof(value.c_str()),
                    [](void *) {});
}

void sqlite3_rstmt::do_bind(int pos) { sqlite3_bind_null(*this->stmt, pos); }

sqlite3_rstmt::~sqlite3_rstmt() { sqlite3_finalize(*this->stmt); }

} // namespace okibank
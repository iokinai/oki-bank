#include "sqlstmt.hxx"

namespace okibank {

sqlstmt::sqlstmt(sqlinnerstmt *stmt) : stmt(stmt) {}

sqlinnerstmt *sqlstmt::get_stmt(void) const noexcept { return this->stmt; }
void sqlstmt::set_stmt(sqlinnerstmt *stmt) noexcept { this->stmt = stmt; }

template <class T> void sqlstmt::bind(int pos, T value) { do_bind(value); }

} // namespace okibank
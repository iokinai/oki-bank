#ifndef APP_INIT_HXX
#define APP_INIT_HXX

#include "concepts.hxx"
#include "database/sqldb.hxx"
#include <string>

namespace okibank::app {

template <sql_database T> T open_db(const std::string &path);
template <sql_database T> void init_db(const T &database);

} // namespace okibank::app

#endif
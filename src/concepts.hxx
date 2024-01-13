#ifndef CONCEPTS_HXX
#define CONCEPTS_HXX

#include "database/sqldb.hxx"
#include <type_traits>

namespace okibank::app {

template <class T>
concept sql_database = std::is_base_of_v<sqldb, T> && !std::is_same_v<sqldb, T>;

}

#endif
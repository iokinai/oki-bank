#ifndef DATABASE_SQLSETTINGS_HXX
#define DATABASE_SQLSETTINGS_HXX

#include <sqlite3.h>

#include <cfg.hxx>

using sqlconnection SHARED_EXPORT = sqlite3;
using sqlinnerstmt SHARED_EXPORT = sqlite3_stmt;

#endif
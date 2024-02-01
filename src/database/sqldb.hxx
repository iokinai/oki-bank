#ifndef DATABASE_SQLDB_HXX
#define DATABASE_SQLDB_HXX

#include "sqlsettings.hxx"
#include "sqlstmt.hxx"
#include <memory>
#include <string>
#include <unordered_map>

#include <cfg.hxx>

// Indicates that the values returns through this parameter
#define _out_

namespace okibank {

using query_result = std::unordered_map<std::string, std::string>;

using query_result_ref = std::shared_ptr<query_result>;

class SHARED_EXPORT sqldb {
protected:
  std::string path;
  sqlconnection **connection;

public:
  virtual ~sqldb() = default;
  sqldb(const sqldb &) = default;
  sqldb(sqldb &&) = delete;
  sqldb &operator=(const sqldb &) = default;
  sqldb &operator=(sqldb &&) = delete;
  sqldb(const std::string &path);
  virtual void prepare(const std::string &stmt, _out_ sqlstmt &rstmt) = 0;
  virtual void send(const sqlstmt &stmt) = 0;
  virtual query_result_ref result(const sqlstmt &stmt) = 0;
  virtual query_result_ref exec(const std::string &stmt) = 0;
};

} // namespace okibank

#endif
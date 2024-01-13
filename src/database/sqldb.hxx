#ifndef DATABASE_SQLDB_HXX
#define DATABASE_SQLDB_HXX

#include "sqlsettings.hxx"
#include "sqlstmt.hxx"
#include <memory>
#include <string>
#include <unordered_map>

#include <cfg.hxx>

namespace okibank {

using query_result = std::unordered_map<std::string, std::string>;

class SHARED_EXPORT sqldb {
protected:
  std::string path;
  sqlconnection **connection;

public:
  virtual ~sqldb() = default;
  sqldb(const std::string &path);
  virtual void prepare(const std::string &stmt, sqlstmt &rstmt) = 0;
  virtual void send(const sqlstmt &stmt) = 0;
  virtual std::shared_ptr<std::unordered_map<std::string, std::string>>
  result(const sqlstmt &stmt) = 0;
};

} // namespace okibank

#endif
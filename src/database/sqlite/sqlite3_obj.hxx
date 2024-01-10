#ifndef DATABASE_SQLITE_SQLITE3_OBJ_HXX
#define DATABASE_SQLITE_SQLITE3_OBJ_HXX

#include <cfg.hxx>
#include <sqlite3.h>
#include <string>

namespace okibank {

class SHARED_EXPORT sqlite3_obj final {
private:
  std::string path;
  sqlite3 **sql3;

public:
  sqlite3_obj(const std::string &path);

  ~sqlite3_obj();
};

} // namespace okibank

#endif
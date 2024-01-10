#include "sqlite3_obj.hxx"
#include "exceptions/sqlite_exception.hxx"

namespace okibank {

sqlite3_obj::sqlite3_obj(const std::string &path) : path(path) {
  int result = sqlite3_open(this->path.c_str(), this->sql3);

  if (result != 0) {
    throw sqlite_exception(result);
  }
}

sqlite3_obj::~sqlite3_obj() { sqlite3_close(*this->sql3); }

} // namespace okibank
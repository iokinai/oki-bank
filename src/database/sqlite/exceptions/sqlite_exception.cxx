#include "sqlite_exception.hxx"

namespace okibank {

sqlite_exception::sqlite_exception(int error) {
  this->error_text.append(std::to_string(error));
}

const char *sqlite_exception::what() const noexcept {
  return this->error_text.c_str();
}

} // namespace okibank
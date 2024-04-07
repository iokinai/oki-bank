#include "endpoint.hxx"

namespace http {

endpoint::endpoint(http_method method, std::string path, parse_handler rhandler)
    : method(method), path(path), rhandler(rhandler) {}

constexpr inline http_method endpoint::get_method() const noexcept {
  return method;
}

constexpr inline const std::string &endpoint::get_path() const noexcept {
  return path;
}

constexpr inline const parse_handler &endpoint::get_rhandler() const noexcept {
  return rhandler;
}

} // namespace http
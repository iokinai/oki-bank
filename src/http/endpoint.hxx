#ifndef HTTP_LLHS_ENDPOINT_HXX
#define HTTP_LLHS_ENDPOINT_HXX

#include "http_method.hxx"
#include "http_types.hxx"
#include <string>

namespace http {

class endpoint {

private:
  http_method method;
  std::string path;
  parse_handler rhandler;

public:
  endpoint(http_method method, std::string path, parse_handler rhandler);
  endpoint(const endpoint &) = default;
  endpoint(endpoint &&) = default;

  endpoint &operator=(const endpoint &) noexcept = default;
  endpoint &operator=(endpoint &&) noexcept = default;

  constexpr inline http_method get_method() const noexcept;
  constexpr inline const std::string &get_path() const noexcept;
  constexpr inline const parse_handler &get_rhandler() const noexcept;
};

} // namespace http

#endif
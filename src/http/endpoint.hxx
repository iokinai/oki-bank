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
  request_handler rhandler;

public:
  endpoint(http_method method, std::string path, request_handler rhandler);
  endpoint(const endpoint &) = default;
  endpoint(endpoint &&) = default;

  endpoint &operator=(const endpoint &) noexcept = default;
  endpoint &operator=(endpoint &&) noexcept = default;

  http_method get_method() const noexcept {
    return method;
  }

  const std::string &get_path() const noexcept {
    return path;
  }

  const request_handler &get_rhandler() const noexcept {
    return rhandler;
  }
};

} // namespace http

#endif
#ifndef HTTP_HTTP_REQUEST_HXX
#define HTTP_HTTP_REQUEST_HXX

#include "http_method.hxx"
#include <cstdint>
#include <string>
#include <vector>

namespace http {

using headers_collection = std::vector<std::pair<std::string, std::string>>;

class http_request {
private:
  std::string url;
  http_method method;
  float version;
  headers_collection headers;
  std::vector<uint8_t> body;

public:
  http_request(const std::string &url, http_method method, float version,
               const headers_collection &headers,
               const std::vector<uint8_t> body);

  http_request(std::string &r);

  http_request(const http_request &) = default;
  http_request(http_request &&) = default;

  http_request &operator=(const http_request &) = default;
  http_request &operator=(http_request &&) = default;

  constexpr inline const std::string &get_url() const noexcept {
    return url;
  }

  constexpr inline http_method get_method() const noexcept {
    return method;
  }

  constexpr inline float get_version() const noexcept {
    return version;
  }

  constexpr inline const headers_collection &get_headers() const noexcept {
    return headers;
  }

  constexpr inline const std::vector<uint8_t> &get_body() const noexcept {
    return body;
  }
};

} // namespace http

#endif
#include "http_method.hxx"

namespace http {

http_method parse_method(const std::string &s) noexcept {
  switch (static_cast<http_method>(hash_method_str(s.c_str()))) {
  case http_method::GET:
    return http_method::GET;
  case http_method::POST:
    return http_method::POST;
  case http_method::PUT:
    return http_method::PUT;
  }
}

} // namespace http
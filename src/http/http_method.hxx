#ifndef HTTP_LLHS_HTTP_METHOD_HXX
#define HTTP_LLHS_HTTP_METHOD_HXX

#include <cstddef>
#include <cstdint>
#include <string>

namespace http {

constexpr size_t strlen_ce(const char *s) noexcept {
  size_t size{0};

  do {
    ++size;
  } while (s[size] != '\0');

  return size;
}

constexpr uint32_t hash_method_str(const char *method) noexcept {
  uint32_t result = 0;

  for (size_t i = 0; i < strlen_ce(method); ++i) {
    result = (result | method[i]) << sizeof(method[i]);
  }

  return result;
}

enum class http_method {
  GET = hash_method_str("GET"),
  POST = hash_method_str("POST"),
  PUT = hash_method_str("PUT"),
};

http_method parse_method(const std::string &s) noexcept;

} // namespace http

#endif
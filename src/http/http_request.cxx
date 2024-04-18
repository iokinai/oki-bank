#include "http_request.hxx"
#include "string_ops.hxx"
#include <cstdint>
#include <vector>

namespace http {

static headers_collection
parse_headers(std::vector<std::string> tokens) noexcept {
  headers_collection result;

  for (int i = 1; tokens[i] != "\r"; ++i) {
    std::vector<std::string> headers = split(tokens[i], ": ");
    result.push_back({headers[0], headers[1]});
  }

  return result;
}

static std::vector<uint8_t> parse_body(std::string &request) noexcept {
  std::vector<std::string> spl = split(request, "\n\n");

  if (spl.size() == 2) {
    return string_into_uint8_t(spl[1]);
  }

  return {};
}

http_request::http_request(const std::string &url, http_method method,
                           float version, const headers_collection &headers,
                           const std::vector<uint8_t> body)
    : url(url), method(method), version(version), headers(headers), body(body) {
}

http_request::http_request(std::string &r) {
  auto tokens = split(r, "\n");

  auto first_str = split(tokens[0], " ");

  method = parse_method(first_str[0]);

  url = first_str[1];

  version = atof(first_str[2].erase(4).c_str());

  headers = parse_headers(tokens);

  body = parse_body(r);
}

} // namespace http
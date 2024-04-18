#ifndef HTTP_STRING_OPS_HXX
#define HTTP_STRING_OPS_HXX

#include <cstdint>
#include <string>
#include <vector>

namespace http {

std::vector<std::string> split(std::string s, const std::string &delimiter);

std::vector<uint8_t> string_into_uint8_t(const std::string &s);

} // namespace http

#endif
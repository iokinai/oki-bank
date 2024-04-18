#ifndef HTTP_LLHS_HTTP_TYPES_HXX
#define HTTP_LLHS_HTTP_TYPES_HXX

#include "http_request.hxx"
#include <functional>
#include <string>

namespace http {

using parse_handler = std::function<void(std::string)>;
using request_handler = std::function<void(const http_request &)>;

} // namespace http

#endif
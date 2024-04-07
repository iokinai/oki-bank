#ifndef HTTP_LLHS_HTTP_TYPES_HXX
#define HTTP_LLHS_HTTP_TYPES_HXX

#include <functional>
#include <string>

namespace http {

using parse_handler = std::function<void(std::string)>;

}

#endif
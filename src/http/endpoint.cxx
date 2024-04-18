#include "endpoint.hxx"

namespace http {

endpoint::endpoint(http_method method, std::string path,
                   request_handler rhandler)
    : method(method), path(path), rhandler(rhandler) {
}

} // namespace http
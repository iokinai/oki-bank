#include "app_init.hxx"
#include "lib/http/httplib.h"
#include <memory>

namespace okibank::app {

std::shared_ptr<Server> create_http_server() {
  Server *s = new Server;

  s->Get("/hw", [](const Request &req, Response &res) {
    res.set_content(
        "Hi! My name is okinai. This is a test endpoint I used to check if the "
        "server works correctly. I have no idea how you got here, but you "
        "should leave.. as fast as possible",
        "text/plain");
  });

  return std::shared_ptr<Server>(s);
}

} // namespace okibank::app
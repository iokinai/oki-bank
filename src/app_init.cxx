#include "app_init.hxx"
#include "http/http_request.hxx"
#include "http/server.hxx"
#include <iostream>
#include <memory>

namespace okibank::app {

std::shared_ptr<server> create_http_server() {
  server *s = new server;

  s->Get("/hw", [](const http_request &req) {
    std::cout << req.get_url() << std::endl;
  });

  return std::shared_ptr<server>(s);
}

} // namespace okibank::app
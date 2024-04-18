#ifndef SERVER_HPP
#define SERVER_HPP

#include "../thread/okijthread.hxx"
#include "endpoint.hxx"
#include "http_types.hxx"
#include "sysdef.hxx"
#include <memory>
#include <vector>

namespace http {

class server {
private:
  socket_t sock;
  std::vector<endpoint> endpoints;
  int backlog;
  std::shared_ptr<okibank::okijthread> listen_thread;

public:
  server(int backlog = 10);

  inline void Get(std::string path, request_handler rhandler) noexcept {
    endpoints.push_back({http_method::GET, path, rhandler});
  }

  inline void Post(std::string path, request_handler rhandler) noexcept {
    endpoints.push_back({http_method::POST, path, rhandler});
  }

  bool listen(std::string host, int port) noexcept;

  ~server();

  //
};

} // namespace http

#endif
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

  static void parse_http_request(std::string request);

public:
  server(int backlog);

  inline void Get(std::string path, parse_handler rhandler) noexcept;
  inline void Post(std::string path, parse_handler rhandler) noexcept;
  bool listen(std::string host, int port) noexcept;

  ~server();

  //
};

} // namespace http

#endif
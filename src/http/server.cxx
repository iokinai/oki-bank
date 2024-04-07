#include "server.hxx"
#include "http_method.hxx"
#include "lowlevel.hxx"
#include <vector>

namespace http {

server::server(int backlog)
    : sock(-1), endpoints(std::vector<endpoint>()), backlog(backlog),
      listen_thread(nullptr) {
  //
}

void server::parse_http_request(std::string request) {}

inline void server::Get(std::string path, parse_handler rhandler) noexcept {
  endpoints.push_back({http_method::GET, path, rhandler});
}

inline void server::Post(std::string path, parse_handler rhandler) noexcept {
  endpoints.push_back({http_method::POST, path, rhandler});
}

bool server::listen(std::string host, int port) noexcept {
  this->sock = create_http_socket();
  http_server_bind(sock, port);

  start_listening(sock, backlog);

  create_listen_thread(sock, parse_http_request);

  return true;
}

server::~server() {
  if (sock != -1) {
    sock_close(sock);
  }
}

} // namespace http
#include "server.hxx"
#include "endpoint.hxx"
#include "http_request.hxx"
#include "lowlevel.hxx"
#include <algorithm>
#include <vector>

namespace http {

server::server(int backlog)
    : sock(-1), endpoints(std::vector<endpoint>()), backlog(backlog),
      listen_thread(nullptr) {
}

bool server::listen(std::string host, int port) noexcept {
  this->sock = create_http_socket();
  try {
    http_server_bind(sock, port);

    start_listening(sock, backlog);

    create_listen_thread(sock, [&](std::string h) {
      http_request r(h);

      auto ep =
          std::find_if(endpoints.cbegin(), endpoints.cend(), [&](endpoint ep) {
            return ep.get_method() == r.get_method() &&
                   ep.get_path() == r.get_url();
          });

      if (ep == endpoints.cend()) {
        return;
      }

      ep->get_rhandler()(r);
    });

    return true;
  } catch (...) {
    sock_close(sock);
    throw;
  }
}

server::~server() {
  if (sock != -1) {
    sock_close(sock);
  }
}

} // namespace http
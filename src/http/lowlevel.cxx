#include "lowlevel.hxx"

#include <cerrno>
#include <exception>
#include <netinet/in.h>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unistd.h>

namespace http {

static std::string read_from_buffer_range(char *buffer, int count) noexcept {
  std::stringstream ss;

  for (int i = 0; i < count; ++i) {
    ss << buffer[i];
  }

  return ss.str();
}

static sockaddr_in get_http_sockaddr(int port) {
  return {.sin_family = AF_INET,
          .sin_port = htons(port),
          .sin_addr = {.s_addr = INADDR_ANY}};
}

uint16_t BUFFER_SIZE = 4096;

socket_t create_http_socket() {
  socket_t sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (sock < 0) {
    throw std::invalid_argument("Couldn't create socket");
  }

  return sock;
}

void sock_close(socket_t sock) {
  close(sock);
}

void http_server_bind(socket_t sock, int port) {
  sockaddr_in addr = get_http_sockaddr(port);

  if (bind(sock, reinterpret_cast<sockaddr *>(&addr), sizeof(sockaddr)) < 0) {
    throw std::invalid_argument(std::to_string(errno));
  }
}

void start_listening(socket_t sock, int backlog) {
  if (listen(sock, backlog) < 0) {
    throw std::exception();
  }
}

okibank::okijthread
create_listen_thread(socket_t sock, const parse_handler &handler) noexcept {
  return okibank::okijthread([=] {
    while (true) {
      sockaddr_in client_addr;
      socklen_t size = sizeof(client_addr);

      socket_t connection =
          accept(sock, reinterpret_cast<sockaddr *>(&client_addr), &size);

      if (connection < 0) {
        continue;
      }

      char *buffer = new char[BUFFER_SIZE];

      int read = recv(connection, buffer, BUFFER_SIZE, 0);

      std::string data = read_from_buffer_range(buffer, read);

      delete[] buffer;

      handler(data);

      close(connection);
    }
  });
}

} // namespace http
#ifndef LOWLEVEL_HPP
#define LOWLEVEL_HPP

#include "../thread/okijthread.hxx"
#include "http_types.hxx"
#include "sysdef.hxx"

namespace http {

socket_t create_http_socket();

void sock_close(socket_t sock);

void http_server_bind(socket_t sock, int port);

void start_listening(socket_t sock, int backlog);

okibank::okijthread create_listen_thread(socket_t sock,
                                         const parse_handler &handler) noexcept;

} // namespace http

#endif
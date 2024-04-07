#ifndef LLHS_SYSDEF_HXX
#define LLHS_SYSDEF_HXX

#ifdef _WIN32

#include <winsock2.h>

using socket_t = SOCKET;

#elifdef __linux__

#include <netinet/in.h>
#include <sys/socket.h>

using socket_t = int;

#endif

#endif
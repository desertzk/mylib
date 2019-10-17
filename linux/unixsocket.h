#pragma once

#include <sys/types.h>          /*  See NOTES */
#include <sys/socket.h>
#include <arpa/inet.h>



#include"sock_clib.h"
#define SOCKET_ERR -1

#ifdef __cplusplus
extern "C" {
#endif
	int socket_init();

	int socket_create(int domain,
		 int type,
		 int protocol);

	void socket_listen(int socksvrfd);

	int tcp_server(int port);

	int tcp_client(const char * ip, int port);

	int tcp_accept(int listensocketfd, struct sockaddr *addr, int *addrlen);

	int tcp_send(int connectsocketfd, const char *sendbuf, int size);

	int tcp_recv(int connectsocketfd, const char *recvbuf, int size);

	int udp_create(const char * ip, int port);

#ifdef __cplusplus
}
#endif

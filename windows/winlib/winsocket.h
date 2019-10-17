#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#include<windows.h>


#ifdef __cplusplus
extern "C" {
#endif
	int socket_init();

	SOCKET socket_create(_In_ int af,
		_In_ int type,
		_In_ int protocol);

	void socket_listen(SOCKET hSockSvr);

	SOCKET tcp_server(int port);

	SOCKET tcp_client(const char * ip, int port);

	SOCKET tcp_accept(SOCKET hListenSocket, struct sockaddr *addr, int *addrlen);

	int tcp_send(SOCKET hConnectSocket, const char *sendbuf, int size);

	int tcp_recv(SOCKET hConnectSocket, const char *recvbuf, int size);

	int udp_create(const char * ip, int port);

#ifdef __cplusplus
}
#endif
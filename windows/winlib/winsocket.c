#define WIN32_LEAN_AND_MEAN
#include"winsocket.h"
#include<stdio.h>
#pragma comment (lib, "ws2_32.lib")

int socket_init()
{
	WSADATA wsa;
	int errnum = WSAStartup(MAKEWORD(2, 2), &wsa);
	if (errnum != 0)
	{
		printf("WSAStartup failed with error: %d\n", errnum);
		return -1;
	}/**/
	return 0;
}

SOCKET socket_create(
	_In_ int af,
	_In_ int type,
	_In_ int protocol)
{
	SOCKET hSockSvr = INVALID_SOCKET;
	hSockSvr = socket(af, type, protocol);
	if (hSockSvr == INVALID_SOCKET)
	{
		printf("socket function failed with error = %d\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	return hSockSvr;
}



SOCKET tcp_server(int port)
{
	SOCKET hSockSvr = socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN svrAddr = { 0 };
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iResult = bind(hSockSvr, (SOCKADDR *)&svrAddr, sizeof (svrAddr));
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error %u\n", WSAGetLastError());
		closesocket(hSockSvr);
		WSACleanup();
		return -1;
	}

	socket_listen(hSockSvr);
	return hSockSvr;
}

void socket_listen(SOCKET hSockSvr)
{
	if (listen(hSockSvr, SOMAXCONN) == SOCKET_ERROR)
		printf("listen function failed with error: %d\n", WSAGetLastError());
}

SOCKET tcp_client(const char * ip, int port)
{
	SOCKET hSockClient = socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN cltAddr = { 0 };
	cltAddr.sin_family = AF_INET;
	cltAddr.sin_port = htons(port);
	cltAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	int iResult = connect(hSockClient, (SOCKADDR*)&cltAddr, sizeof(cltAddr));
	if (iResult == SOCKET_ERROR) {
		printf("connect function failed with error: %ld\n", WSAGetLastError());
		iResult = closesocket(hSockClient);
		if (iResult == SOCKET_ERROR)
			printf("closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return -1;
	}
	return hSockClient;
}


SOCKET tcp_accept(SOCKET hListenSocket, struct sockaddr *addr, int *addrlen)
{
	SOCKET AcceptSocket = INVALID_SOCKET;
	wprintf(L"Waiting for client to connect...\n");

	// Accept the connection.
	AcceptSocket = accept(hListenSocket, addr, addrlen);
	if (AcceptSocket == INVALID_SOCKET) {
		wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		closesocket(hListenSocket);
		WSACleanup();
		return -1;
	}
	else
		wprintf(L"Client connected.\n");

	return AcceptSocket;
}

int tcp_send(SOCKET hConnectSocket, const char *sendbuf, int size)
{
	int iResult = send(hConnectSocket, sendbuf, size, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(hConnectSocket);
		WSACleanup();
		return -1;
	}

	//sendbuf not equal want send
	if (iResult != size)
	{
		printf("Bytes Sent: %d\n", iResult);
		//return iResult;
		//try resend
	}
	return iResult;
}

int tcp_recv(SOCKET hConnectSocket, const char *recvbuf,int size)
{
	int iResult = recv(hConnectSocket, recvbuf, size, 0);
	if (iResult > 0)
		printf("Bytes received: %d\n", iResult);
	else if (iResult == 0)
		printf("Connection closed\n");
	else
		printf("recv failed: %d\n", WSAGetLastError());
	return iResult;
}



int udp_create(const char * ip, int port)
{
	SOCKET hSockSvr = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	SOCKADDR_IN svrAddr = { 0 };
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iResult = bind(hSockSvr, (SOCKADDR *)&svrAddr, sizeof (svrAddr));
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error %u\n", WSAGetLastError());
		closesocket(hSockSvr);
		WSACleanup();
		return -1;
	}
}



//void main()
//{
//	socket_init();
//	TCPServer(29007);
//	getchar();
//}
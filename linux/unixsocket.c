#include"unixsocket.h"


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

int socket_create(int domain,int type, int protocol)
{
	int sockfd = socket(domain, type, protocol);
	if (sockfd == SOCKET_ERR)
	{
		ERR_RETURN("socket function failed with error");
		return -1;
	}
	return sockfd;
}



int tcp_server(int port)
{
	int socksvrfd = socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	struct sockaddr_in svrAddr = { 0 };

	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iResult = bind(socksvrfd, (SOCKADDR *)&svrAddr, sizeof (svrAddr));
	if (iResult == SOCKET_ERR) {
		ERR_RETURN("bind failed with error");
		close(socksvrfd);
		return -1;
	}

	socket_listen(socksvrfd);
	return socksvrfd;
}

void socket_listen(int socksvrfd)
{
	if (listen(socksvrfd, SOMAXCONN) == SOCKET_ERR)
		ERR_RETURN("listen function failed with error");
}

int tcp_client(const char * ip, int port)
{
	int hSockClient = socket_create(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in cltAddr = { 0 };
	cltAddr.sin_family = AF_INET;
	cltAddr.sin_port = htons(port);
	cltAddr.sin_addr.S_un.S_addr = inet_addr(ip);
	int iResult = connect(hSockClient, (SOCKADDR*)&cltAddr, sizeof(cltAddr));
	if (iResult == SOCKET_ERR) {
		ERR_RETURN("connect function failed with error");
		iResult = close(hSockClient);
		if (iResult == ERROR)
			ERR_RETURN("close function failed with error");
		return ERROR;
	}
	return hSockClient;
}


int tcp_accept(int listensocketfd, struct sockaddr *addr, int *addrlen)
{
	printf("Waiting for client to connect...\n");
  char ipstr[64]={0};
	// Accept the connection.
	int acceptsocketfd = accept(listensocketfd, addr, addrlen);
	if (acceptsocketfd == SOCKET_ERR) {
		ERR_RETURN("accept failed with error");
		close(listensocketfd);  
		return ERROR;
	}
	else
		printf("Client connected IP %s\t.PORT %d\t\n",
        inet_ntop(AF_INET,&addr.sin_addr.S_addr,ipstr,sizeof(ipstr)),addr.sin_port);

	return acceptsocketfd;
}

int tcp_send(int connectsocketfd, const char *sendbuf, int size)
{
	int iResult = send(connectsocketfd, sendbuf, size, 0);
	if (iResult == SOCKET_ERR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		close(connectsocketfd);
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

int tcp_recv(int connectsocketfd, const char *recvbuf,int size)
{
	int iResult = recv(connectsocketfd, recvbuf, size, 0);
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
	int socksvrfd = socket_create(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	
	struct sockaddr_in svrAddr = { 0 };
	svrAddr.sin_family = AF_INET;
	svrAddr.sin_port = htons(port);
	svrAddr.sin_addr.S_un.S_addr = INADDR_ANY;
	int iResult = bind(socksvrfd, (SOCKADDR *)&svrAddr, sizeof (svrAddr));
	if (iResult == int_ERROR) {
		printf("bind failed with error %u\n", WSAGetLastError());
		close(socksvrfd);
		return -1;
	}
}



//void main()
//{
//	socket_init();
//	TCPServer(29007);
//	getchar();
//}

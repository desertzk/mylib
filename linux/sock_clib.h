#ifndef SOCK_CLIB_H_
#define SOCK_CLIB_H_

#ifdef __cplusplus
extern 'C'
{
#endif // __cplusplus

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include<unistd.h>
#include <fcntl.h>

#define Sck_Ok  0
#define Sck_BaseErr 3000


#define Sck_ErrParam       Sck_BaseErr+1
#define Sck_ErrTimeOut     Sck_BaseErr+2
#define Sck_ErrPeerClosed  Sck_BaseErr+3
#define Sck_ErrMalloc      Sck_BaseErr+4

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while(0)

#define ERR_RETURN(m) \
    do \
    { \
        perror(m); \
        return errno; \
    }while(0)


int active_nonblock(int fd);
int deactivate_nonblock(int fd);

int read_timeout(int fd,unsigned int wait_seconds);
int write_timeout(int fd,unsigned int wait_seconds);
int accept_timeout(int fd,struct sockaddr *addr,unsigned int wait_seconds);
int connect_timeout(int fd,struct sockaddr *addr,unsigned int wait_seconds);

ssize_t readn(int fd,const void *buf,size_t count);
ssize_t writen(int fd,const void *buf,size_t count);
ssize_t recv_peek(int sockfd,void *buf,size_t len);
ssize_t readline(int sockfd,void *buf,size_t maxline);

//next few lines is about business   client
//int sckClient_init(void **handle,int contime,int sendtime,int recvtime,int connNum);
int sckClient_init(void **handle,int count);

int sckClient_getconnect(void *handle,char *ip,int port,int contime);

int sckClient_send(void *handle,char *data,size_t datalen, int sendtime);
//int sckClient_send(void *handle,int connfd,unsigned char *data,int datalen,int sendtime);
int sckClient_rev(void *handle,char *out,size_t *outlen,int recvtime);
//int sckClient_rev(void *handle,int connfd,unsigned char *out,int *outlen,int recvtime);

int sckClient_putconn(int connfd);

int sckClient_closeconn(int connfd);

int sckClient_destroy(void *handle);

//--------------------------------------------server---------------
//server
int sckServer_init(int *listenfd,int port);



int sckServer_accept(int listened,int *connfd,int timeout);

int sckServer_send(int connfd,unsigned char *data,int datalen,int timeout);

int sckServer_rev(int connfd,unsigned char *out,int *outlen,int timeout);


int sckServer_destroy(void *handle);



#ifdef __cplusplus
}
#endif // __cplusplus

#endif




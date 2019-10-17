#include "sock_clib.h"
#include<time.h>
#include <arpa/inet.h>

typedef struct __SckHandle
{

    int sockfd;
    int sockArray[10];
    int arraynum;

}SckHandle;

//读取固定字节数，失败返回-1
ssize_t readn(int fd,const void *buf,size_t count)
{
    size_t nleft=count;
    ssize_t nread;
    char *bufp=(char *)buf;

    while(nleft>0)
    {
        if((nread=read(fd,bufp,nleft))<0)
        {
            if(errno==EINTR)
                continue;
            return -1;
        }else if(nread==0)
            return count-nleft;
        bufp+=nread;
        nleft-=nread;
    }

    return count;
}

//发送固定字节，失败返回-1
ssize_t writen(int fd,const void *buf,size_t count)
{
    size_t nleft=count;
    ssize_t nwritten;
    char *bufp=(char *)buf;

    while(nleft>0)
    {
        if((nwritten=write(fd,bufp,nleft))<0)
        {

            if(errno==EINTR)
                continue;
            return -1;
            }else if(nwritten==0)
                continue;

            bufp+=nwritten;
            nleft-=nwritten;
    }
    return count;
}

//仅仅查看字节缓冲区，但不移除数据
ssize_t recv_peek(int sockfd,void *buf,size_t len)
{
    while(1)
    {
        int ret =recv(sockfd,buf,len,MSG_PEEK);
        if(ret==-1&&errno==EINTR)
            continue;
        return ret;
    }
}


ssize_t readline(int sockfd,void *buf,size_t maxline)
{
    int ret;
    int nread;
    char *bufp=buf;
    int nleft=maxline;
    while(1)
    {
        ret=recv_peek(sockfd,bufp,nleft);
        if(ret<0)
            return ret;
        else if(ret==0)
            return ret;
        nread=ret;
        int i;
        for(i=0;i<nread;i++)
        {
            if(bufp[i]=='\n')
            {
                ret=readn(sockfd,bufp,i+1);
                if(ret!=i+1)
                    exit(EXIT_FAILURE);

                return ret;
            }
        }

        if(nread>nleft)
            exit(EXIT_FAILURE);

        nleft-=nread;
        ret=readn(sockfd,bufp,nread);
        if(ret!=nread)
            exit(EXIT_FAILURE);

        bufp+=nread;
    }

    return -1;
}

//设置为非阻塞
int activate_nonblock(int fd)
{
    int ret=0;
    int flags=fcntl(fd,F_GETFL);
    if(flags==-1)
    {
        ret=flags;
        printf("active_nonblock error\n");
        return ret;
    }

    flags|=O_NONBLOCK;
    ret=fcntl(fd,F_SETFL,flags);
    if(ret==-1)
    {
        printf("active_nonblock error\n");
        return ret;
    }
    return ret;
}

/*
设置为阻塞模式
*/
int deactivate_nonblock(int fd)
{
    int ret=0;
    int flags=fcntl(fd,F_GETFL);
    if(flags==-1)
    {
        ret=flags;
        printf("deactivate_nonblock error\n");
        return ret;
    }

    flags&=~O_NONBLOCK;
    ret=fcntl(fd,F_SETFL,flags);
    if(ret==-1)
    {
        printf("deactivate_nonblock error\n");
        return ret;
    }
    return ret;
}


int connect_timeout(int fd,struct sockaddr *addr,unsigned int wait_seconds)
{
    if(addr==NULL||wait_seconds<0)
        return -1;
    int ret;
    socklen_t addrlen=sizeof(struct sockaddr_in);
    activate_nonblock(fd);
    ret=connect(fd,addr,addrlen);
    if(ret<0&&errno==EINPROGRESS)//如果正在处理则设置等待时间
    {
        fd_set connect_fdset;
        struct timeval timeout;
        FD_ZERO(&connect_fdset);
        FD_SET(fd,&connect_fdset);
        timeout.tv_sec=wait_seconds;
        timeout.tv_usec=0;
        do
        {
            ret=select(fd+1,NULL,&connect_fdset,NULL,&timeout);
        }while(ret<0&&errno==EINTR);
        if(ret==0)
        {
            ret=-1;
            errno=ETIMEDOUT;
        }
        else if(ret<0)
            return -1;
        else if(ret==1)
        {
        //ret返回为1,可能有两种情况一种是连接建立成功，一种是套接字产生错误
            int err;
            socklen_t socklen=sizeof(err);
            int sockoptret=getsockopt(fd,SOL_SOCKET,SO_ERROR,&err,&socklen);
            if(sockoptret==-1)
            {
                printf("connect error\n");
                return -1;
            }
            if(err==0)
            {
                ret=0;
            }
            else
            {
                errno=err;
                ret=-1;
            }
        }
    }
    deactivate_nonblock(fd);
}

//wrap accept to handle signal
int Accept(int fd,struct sockaddr *sa,socklen_t *salenptr)
{
  int n;

again:
  if((n=accept(fd,sa,salenptr))<0)
  {
    if((errno==ECONNABORTED)||(errno==EINTR))
    {
      goto again;
    }else{
      ERR_RETURN("accept error\n");
    }
  }
  return n;
}


ssize_t Read(int fd,void *ptr,size_t nbytes)
{
  ssize_t n;
again:
  if((n=read(fd,ptr,nbytes))==-1)
  {
    if(errno==EINTR)
      goto again;
    else
      return -1;
  }

  return n;
}


ssize_t Write(int fd,void *ptr,size_t nbytes)
{
  ssize_t n;
again:
  if( (n=write(fd,ptr,nbytes))==-1)
  {
    if(errno==EINTR)
      goto again;
    else
      return -1;
  }

  return n;
}

/*
-1 select error -2timeout -3 param error
*/
int accept_timeout(int fd,struct sockaddr *addr,unsigned int wait_seconds)
{
    int ret=0;


    if(wait_seconds<0||addr==NULL||fd<0)
    {
        return -3;
    }
    fd_set accept_fdset;
    struct timeval timeout;
    FD_ZERO(&accept_fdset);
    FD_SET(fd,&accept_fdset);
    timeout.tv_sec=wait_seconds;
    timeout.tv_usec=0;
    do
    {
        ret=select(fd+1,&accept_fdset,NULL,NULL,&timeout);
    }while(ret<0&&errno==EINTR);
    if(ret==-1)
        return -1;
    else if(ret==0)
    {
        errno=ETIMEDOUT;
        return -2;
    }

    socklen_t addrlen=sizeof(struct sockaddr);
    return Accept(fd,addr,&addrlen);
}


int read_timeout(int fd,unsigned int wait_seconds)
{
    int ret=0;
    if(wait_seconds<0)
    {
        return -1;
    }
    fd_set read_fdset;
    struct timeval timeout;

    FD_ZERO(&read_fdset);
    FD_SET(fd,&read_fdset);

    timeout.tv_sec=wait_seconds;
    timeout.tv_usec=0;

    do
    {
        ret=select(fd+1,&read_fdset,NULL,NULL,&timeout);
    }while(ret<0&&errno==EINTR);//it perhaps interrupt by signal

    if(ret==0)
    {
        ret=-1;
        errno=ETIMEDOUT;
    }
    else if(ret==1)
        ret=0;
    return ret;
}

int write_timeout(int fd,unsigned int wait_seconds)
{
     int ret=0;
    if(wait_seconds>0)
    {
        fd_set write_fdset;
        struct timeval timeout;

        FD_ZERO(&write_fdset);
        FD_SET(fd,&write_fdset);

        timeout.tv_sec=wait_seconds;
        timeout.tv_usec=0;
        do
        {
            ret=select(fd+1,NULL,&write_fdset,NULL,&timeout);
        }while(ret<0&&errno==EINTR);
        if(ret==0)
        {
            ret=-1;
            errno=ETIMEDOUT;
        }else if(ret==1)
            return 0;

    }
    return ret;
}

int sckClient_init(void **handle,int count)
{
    if(handle==NULL||count<0)
    {
        printf("sckinit param error\n");
        return Sck_ErrParam;
    }
    SckHandle *tmp=(SckHandle *)malloc(sizeof(SckHandle));
    if(tmp==NULL)
    {
        printf("SckHandle malloc error\n");
        return Sck_ErrMalloc;
    }

    tmp->arraynum=count;

    int i=0;
    for(i=0;i<count;i++)
    {
         int sockfd;
         if((sockfd=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
            ERR_RETURN("socket");

        tmp->sockArray[i]=sockfd;
        tmp->arraynum++;
    }



    *handle=tmp;
    return 0;
}




int sckClient_getconnect(void *handle,char *ip,int port, int contime)
{
    if(handle==NULL||ip==NULL||port<0||port>65535)
    {
         printf("sckClient_getconnect param error\n");
         return Sck_ErrParam;
    }
    SckHandle *tmp=handle;

    int i=0;
    //0 stdin 1stdout 2stderr
    for(i=0;i<tmp->arraynum;i++)
    {
        if(tmp->sockArray[0]>0)
        {
            tmp->sockfd=tmp->sockArray[0];
            break;
        }
    }


    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    servaddr.sin_addr.s_addr=inet_addr(ip);
    tmp=(SckHandle *)handle;

    int ret=connect_timeout(tmp->sockfd,(struct sockaddr*)&servaddr,contime);
    if(ret<0)
        ERR_EXIT("connect_timeout\n");

    //*sockfd=tmp->sockfd;
    return 0;

}

int sckClient_send(void *handle,char *data,size_t datalen, int sendtime)
{
    int ret=0;
    SckHandle *tmp=NULL;
    tmp=(SckHandle *)handle;

    ret=write_timeout(tmp->sockfd,sendtime);
    if(ret==0)
    {
        unsigned char *netdata=(unsigned char *)malloc(datalen+4);//..............remember free
        if(netdata==NULL)
        {
            printf("sckClient_send err\n");
            return Sck_ErrMalloc;
        }
        int netlen=htonl(datalen);
        memcpy(netdata,&netlen,4);
        memcpy(netdata+4/**/,data,datalen);
        int writed=writen(tmp->sockfd,netdata,datalen+4);
        if(writed<datalen+4)
        {
            if(netdata!=NULL)
            {
                free(netdata);
                netdata=NULL;
            }
            return writed;
        }
        if(netdata!=NULL)
        {
                free(netdata);
                netdata=NULL;
        }
    }
    if(ret<0)
    {
        if(ret==-1&&errno==ETIMEDOUT)
        {
            printf("sckClient_send error\n");
            return ret=Sck_ErrTimeOut;
        }
        return ret;
    }

    return ret;
}

int sckClient_rev(void *handle,char *out,size_t *outlen,int recvtime)
{
    if(NULL==handle||NULL==out||NULL==outlen||recvtime<0)
    {
        printf("sckClient_rev param err\n");
        return Sck_ErrParam;
    }

    int ret=0;
    SckHandle *tmp=NULL;
    tmp=(SckHandle *)handle;
    ret=read_timeout(tmp->sockfd,recvtime);
    if(ret!=0)
    {
        if(ret==-1||errno==ETIMEDOUT)
        {
             printf("sckClient_rev Sck_ErrTimeOut\n");
             ret=Sck_ErrTimeOut;
        }else{
            printf("sckClient_rev error\n");
        }
    }
    int netdatalen=0;
    ret=readn(tmp->sockfd,&netdatalen,4);
    if(ret==-1)
    {
        printf("readn err\n");
        return ret;
    }else if(ret<4){
        printf("readn err peer close\n");
        return Sck_ErrPeerClosed;
    }

    int netnum=ntohl(netdatalen);
    ret=readn(tmp->sockfd,out,netnum);
     if(ret==-1)
    {
        printf("readn err\n");
        return ret;
    }else if(ret<netnum){
        printf("readn err peer close\n");
        return Sck_ErrPeerClosed;
    }
    *outlen=netnum;

    return 0;

}


int sckClient_destroy(void *handle)
{
    if(handle!=NULL)
    {
        free(handle);
        handle=NULL;
    }
    return 0;
}

int sckClient_closeconn(int connfd)
{
    if(connfd>=0)
    {
        close(connfd);
    }
}

//-----------------------server---------------------
int sckServer_init(int *listenfd,int port)
{
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port=htons(port);
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

    if((*listenfd=socket(PF_INET,SOCK_STREAM,0))<0)
        ERR_RETURN("socket");

    int on=1;
    int ret=0;
    if((ret=setsockopt(*listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on))<0))
            ERR_RETURN("setsockopt");

    if(bind(*listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        ERR_RETURN("bind");
    if(listen(*listenfd,SOMAXCONN)<0)
        ERR_RETURN("listen");
    return 0;
}



int sckServer_accept(int listened,int *connfd,int timeout)
{
    struct sockaddr_in peeraddr;
    memset(&peeraddr,0,sizeof(peeraddr));
    int ret=accept_timeout(listened,&peeraddr,timeout);
    if(ret<0)
    {
        if(ret==-2)
        {
            printf("sckServer_accept wait timeout\n");
            return Sck_ErrTimeOut;
        }
         ERR_RETURN("accept_timeout");
    }

    *connfd=ret;
    return 0;

}

int sckServer_send(int connfd,unsigned char *data,int datalen,int timeout)
{
    int ret=0;


    ret=write_timeout(connfd,timeout);
    if(ret==0)
    {
        unsigned char *netdata=(unsigned char *)malloc(datalen+4);//..............remember free
        if(netdata==NULL)
        {
            printf("sckClient_send err\n");
            return Sck_ErrMalloc;
        }
        int netlen=htonl(datalen);
        memcpy(netdata,&netlen,4);
        memcpy(netdata+4/**/,data,datalen);
        int writed=writen(connfd,netdata,datalen+4);
        if(writed<datalen+4)
        {
            if(netdata!=NULL)
            {
                free(netdata);
                netdata=NULL;
            }
            return writed;
        }
        if(netdata!=NULL)
        {
                free(netdata);
                netdata=NULL;
        }
    }
    if(ret<0)
    {
        if(ret==-1&&errno==ETIMEDOUT)
        {
            printf("sckServer_send error\n");
            return ret=Sck_ErrTimeOut;
        }
        return ret;
    }

    return ret;
}

int sckServer_rev(int connfd,unsigned char *out,int *outlen,int timeout)
{
     if(connfd<0||NULL==out||NULL==outlen||timeout<0)
    {
        printf("sckClient_rev param err\n");
        return Sck_ErrParam;
    }

    int ret=0;

    ret=read_timeout(connfd,timeout);
    if(ret!=0)
    {
        if(ret==-1||errno==ETIMEDOUT)
        {
             printf("sckClient_rev Sck_ErrTimeOut\n");
             ret=Sck_ErrTimeOut;
        }else{
            printf("sckClient_rev error\n");
        }
    }
    int netdatalen=0;
    ret=readn(connfd,&netdatalen,4);
    if(ret==-1)
    {
        printf("readn err\n");
        return ret;
    }else if(ret<4){
        printf("readn err peer close\n");
        return Sck_ErrPeerClosed;
    }

    int netnum=ntohl(netdatalen);
    ret=readn(connfd,out,netnum);
     if(ret==-1)
    {
        printf("readn err\n");
        return ret;
    }else if(ret<netnum){
        printf("readn err peer close\n");
        return Sck_ErrPeerClosed;
    }
    *outlen=netnum;

    return 0;

}


int sckServer_destroy(void *handle)
{

}

int main1()
{
    void *handle=NULL;
    char *data="zzzzzzkkkkkkk";
    size_t datalen=strlen(data);

    int count =3;//not used
    unsigned char out[1024];
    unsigned int outlen=1024;
    sckClient_init(&handle,10);

    int ret=sckClient_getconnect(handle,"127.0.0.1",8001,5);

    ret=sckClient_send(handle,data,datalen,5);
    if(ret==Sck_ErrTimeOut)
    {
        int ret=sckClient_send(handle,data,datalen,5);
        printf("first send timeout");
    }else if(ret<0)
    {
        ret=sckClient_getconnect(handle,"127.0.0.1",8001,count);
    }


    sckClient_rev(handle,out,outlen,5);
    sckClient_destroy(handle);

    return 0;
}

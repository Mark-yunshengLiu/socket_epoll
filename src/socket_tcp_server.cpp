/**
 * ClassName: socket_tcp_server
 * Description: socket tcp server
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/20
 * Version: V1.0
 * QQ:120772981
 **/ 

#include "socket_tcp_server.h"
 
void onconnected(int sockfd)                             
{
    perror("this is new a connection!");
}

void onrecv(int pclientfd, char* precvbuf, unsigned int precvLen)                
{
    perror("new data received!");
    //将接收数据放入任务池队列，
    //在服务初始化时创建线程池进行对任务池消费，满足生产消费模式平衡
    //根据需要采用并行模式对任务池待处理任务进行并发性执行饱和线程，进而提高服务处理机能
}

void onclose(int psockfd)                                  
{
    perror("close clt!");
}

int socket_tcp_server::init_server()
{
    struct sockaddr_in serverSockaddr;
    int sockfd, on = 0;
    if((sockfd=socket(AF_INET,SOCK_STREAM,0))==-1) {
        perror("create socket error!");
        return -1;
    }

    serverSockaddr.sin_family=AF_INET;
    serverSockaddr.sin_port=htons(SERVER_PORT);
    serverSockaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    bzero(&(serverSockaddr.sin_zero),8);  
    setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on)); 

    if(bind(sockfd,(struct sockaddr *)&serverSockaddr,sizeof(struct sockaddr))==-1) {
        perror("bind error!");
        return -1;
    } 
    if(listen(sockfd,SERVER_CON_MAX_QUEUE)==-1) {
        perror("listen error!");
        return -1;
    } 
    epoll.reg_callback(onconnected, onrecv, onclose);
    epoll.init_epoll(sockfd); 
} 
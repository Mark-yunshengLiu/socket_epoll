/**
 * ClassName: socket_epoll
 * Description: socket epoll
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/20
 * Version: V1.0
 * QQ:120772981
 **/ 
#ifndef _SERVER_EPOLL_H_
#define _SERVER_EPOLL_H_

#include <sys/epoll.h>
#include <string.h>  clas
 
#define EPOLL_MAX_EVENTS 200 //考虑内存大小 
#define EPOLL_CLT_MAX_RECV_SIZE 4096
class socket_epoll 
{ 
public: 
    typedef void (*ONCLTCONNECTED)(int psockfd);                             //定义连接事件OnConnected 
    typedef void (*ONCLTRECV)(int pcltfd, char* precvbuf, unsigned int precvLen);                 //定义当有数据接收事件 
    typedef void (*ONCLTCLOSE)(int psockfd);                                 //定义连接断开事件
private:
	ONCLTCONNECTED			oncltconnected = NULL;				            // 客户端连接事件，回调函数	
	ONCLTCLOSE              oncltclose = NULL;					            // 客户端断开连接
    ONCLTRECV		        oncltrecv = NULL;						        // 客户端接收数据
public: 
    void reg_callback(ONCLTCONNECTED pcltconn, ONCLTRECV pcltrecv, ONCLTCLOSE pcltclose); 
    int init_epoll(int psockfd); 
    int on_accept_conn(int psockfd,int pepollfd);
    int on_accept_recv(int pcltfd);
};
#endif
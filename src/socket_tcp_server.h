/**
 * ClassName: socket_tcp_server
 * Description: socket tcp server
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/20
 * Version: V1.0
 * QQ:120772981
 **/ 
#ifndef _SOCKET_TCP_SERVER_H_
#define _SOCKET_TCP_SERVER_H_

#include <stdio.h>
#include <netdb.h>
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#include "socket_epoll.h"

#define SERVER_PORT 8000
#define SERVER_CON_MAX_QUEUE 20
 
class socket_tcp_server {
    private:
        socket_epoll epoll;
    public: 
        int init_server();
}; 
#endif
  
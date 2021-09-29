/**
 * ClassName: socket_epoll
 * Description: socket epoll
 * Author: Mark yunsheng.Liu
 * Date: 2021/05/20
 * Version: V1.0
 * QQ:120772981
 **/ 
#include <stdio.h>
#include "unistd.h"
#include "netinet/in.h"
#include "sys/socket.h"
#include "socket_epoll.h" 
  
void socket_epoll::reg_callback(ONCLTCONNECTED pcltconn, ONCLTRECV pcltrecv, ONCLTCLOSE pcltclose)
{
    this->oncltconnected = pcltconn;
    this->oncltrecv = pcltrecv;
    this->oncltclose = pcltclose;
}

int socket_epoll::init_epoll(int psockfd)
{  
    int epollfd; 
    struct epoll_event eventList[EPOLL_MAX_EVENTS];
    epollfd=epoll_create(EPOLL_MAX_EVENTS);
    struct epoll_event event;
    event.events = EPOLLIN|EPOLLET;
    event.data.fd = psockfd;
    if(epoll_ctl(epollfd,EPOLL_CTL_ADD, psockfd, &event) < 0) {
         printf("epoll 加入失败 fd:%d\n", psockfd);
         return -1;
    }  
    bool berror = false;
    while(!berror) {
        int timeout = 300;  
        int ret = epoll_wait(epollfd, eventList, EPOLL_MAX_EVENTS, timeout); 
        if(ret < 0) {
             perror("epoll error\n");
             berror =true;
             break;
        }  
        else if(ret == 0) {
            continue; 
        }  

        for(int i = 0; i < ret; i++) { 
            if(eventList[i].events & EPOLLERR || (eventList[i].events & EPOLLHUP) || !(eventList[i].events & EPOLLIN)) {
                perror("epoll error\n");
                close(eventList[i].data.fd); 
                berror =true;
                break;
            }
            
            if(eventList[i].data.fd == psockfd) {
                this->on_accept_conn(psockfd, epollfd);
            }
            else{
                this->on_accept_recv(eventList[i].data.fd);
            }
        } 
    }

    return 0;
}
 
int socket_epoll::on_accept_conn(int psockfd,int pepollfd)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(struct sockaddr_in);
    bzero(&sin, len); 
    int cltfd = accept(psockfd, (struct sockaddr *)&sin, &len); 
    if(cltfd < 0) {
        perror("connect error\n");
        return -1;
    }
 
    struct epoll_event event;
    event.data.fd = cltfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(pepollfd, EPOLL_CTL_ADD, cltfd, &event); 

    //TODO:可耦合直接写逻辑接连逻辑 , 或推送至其他调用接口组装
    if(this->oncltconnected  != NULL) {
        this->oncltconnected(cltfd);
    }

    return 1;
}

int socket_epoll::on_accept_recv(int pcltfd)
{
    int recvLen=0;
    char recvBuf[EPOLL_CLT_MAX_RECV_SIZE];
    memset(recvBuf, 0, sizeof(recvBuf));
    recvLen = recv(pcltfd,(char *)recvBuf, EPOLL_CLT_MAX_RECV_SIZE, 0);
    if(recvLen == 0) {
        return -1;
    } 
    else if(recvLen < 0) {
        perror("recv Error");
        return -1;
    }

    //TODO: 可耦合直接写逻辑接连逻辑, 或推送至其他类至回调进行组织通讯逻辑
    if(this->oncltrecv != NULL) {
        this->oncltrecv(pcltfd,recvBuf,recvLen);
    }
}
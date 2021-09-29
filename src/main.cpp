#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<errno.h>
 
#include "socket_tcp_server.h"

int main()
{
    socket_tcp_server* server = new socket_tcp_server();
    server->init_server();

    fprintf(stderr,"123123 !\n");




    // int sockfd;
    // int port = 5000;
    // struct hostent* host;
    // struct sockaddr_in server_addr;
    // sockfd=socket(AF_INET,SOCK_STREAM,0);
     
    // if(sockfd < 0)
    // {
    //     fprintf(stderr,"Socket Error:%s\a\n",strerror(errno)); 
    //     return 0;
    // }

    // host = gethostbyname("192.168.1.106");
 
    // bzero(&server_addr,sizeof(server_addr));
    // server_addr.sin_family = AF_INET;
    // server_addr.sin_port = htons(port);
    // server_addr.sin_addr = *((struct in_addr*)host->h_addr);

    // int iConnVal = connect(sockfd,(struct sockaddr *)(&server_addr),sizeof(struct sockaddr));
    
    // if(iConnVal != 0) 
    // {
    //     fprintf(stderr,"AAA:%d Socket Error:%s\a\n",iConnVal,strerror(errno)); 
    //     return 0;
    // }
    // char sendbuffer[200];
    // memcpy(sendbuffer,"123456789",200);
    // send(sockfd,sendbuffer,sizeof(sendbuffer),0);
    return 0;
}
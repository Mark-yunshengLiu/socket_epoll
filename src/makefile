build : test01.o socket_tcp_server.o socket_epoll.o 
	g++ -o build  test01.o socket_tcp_server.o socket_epoll.o 
test01.o :  main.cpp socket_tcp_server.h
	g++ -g -c main.cpp
socket_tcp_server.o : socket_tcp_server.h socket_tcp_server.cpp socket_epoll.h
	g++ -g -c socket_tcp_server.cpp
socket_epoll.o : socket_epoll.h socket_epoll.cpp
	g++ -g -c socket_epoll.cpp
clean :
	rm test01.o socket_tcp_server.o socket_epoll.o build
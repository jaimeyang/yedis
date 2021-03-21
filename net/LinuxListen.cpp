//
// Created by jaime on 2021/3/21.
//

#include "LinuxListen.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstring>

void yedis::LinuxListen::listenServer(const string& addr,int port) {
    auto fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0) {
        cout<<"LinuxListen error "<<strerror(errno)<<endl;
        return;
    }
    sockaddr_in sock;
    bzero(&sock,sizeof(addr));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr =  inet_addr(addr.c_str());

    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    if ( bind(fd,(struct sockaddr*)&addr,sizeof(addr)) < 0 ){
        std::cout<<"bind error "<<errno<<std::endl;
        return;
    }

    if (listen(fd,65553) < 0){
        std::cout<<"listen error "<<strerror(errno)<<std::endl;
        return;
    }

}

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
#include "LinuxStream.h"

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
    this->acceptServer(fd);
}

void yedis::LinuxListen::acceptServer(int fd) {
    while (true) {
        sockaddr addr;
        auto err = accept(fd, &addr, reinterpret_cast<socklen_t *>(sizeof(sockaddr)));
        if (err < 0) {
            cout<<"linux acceptserver err is "<<strerror(errno)<<endl;
            continue;
        }
        this->m_io->addFd(fd);
    }

}

void yedis::LinuxListen::bindMIo(yedis::IMultiIo *io) {
    this->m_io = io;
}


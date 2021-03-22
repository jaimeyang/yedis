//
// Created by jaime on 2021/3/21.
//

#include "LinuxListen.h"
#include "LinuxStream.h"

void yedis::LinuxListen::listenServer(const string& addr,int port) {
    auto fd = socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0) {
        cout<<"LinuxListen error "<<strerror(errno)<<endl;
        return;
    }
    sockaddr_in sock;
    bzero(&sock,sizeof(sockaddr_in));
    sock.sin_family = AF_INET;
    sock.sin_port = htons(port);
    sock.sin_addr.s_addr =  inet_addr(addr.c_str());

    int reuse = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    if ( bind(fd,(struct sockaddr*)&sock,sizeof(sock)) < 0 ){
        std::cout<<"bind error "<<strerror(errno)<<std::endl;
        return;
    }

    if (listen(fd,65553) < 0){
        std::cout<<"listen error "<<strerror(errno)<<std::endl;
        return;
    }
    socklen_t len = sizeof(sock);
    this->acceptServer(fd,sock,&len);
}

void yedis::LinuxListen::acceptServer(int fd,sockaddr_in addr,socklen_t* len) {
    while (true) {
        auto err = accept(fd, (sockaddr*)&addr, len);
        if (err < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue;
            }
            cout<<"linux acceptserver err is "<<strerror(errno)<<endl;
            continue;
        }
        cout<<"accept "<<err<<endl;
        this->m_io->addFd(err);
    }

}

void yedis::LinuxListen::bindMIo(yedis::IMultiIo *io) {
    this->m_io = io;
}


//
// Created by jaime on 2021/1/29.
//

#include "ServerObj.h"
#include <sys/socket.h>
#include <iostream>

void ServerObj::acceptServer(int fd) {
    struct sockaddr addr;
    socklen_t len;
    auto new_fd = accept(fd,&addr,&len);
    if ( new_fd < -1 ){
        std::cout<<"accept error "<<errno<<std::endl;
        return;
    }
}

void ServerObj::writeEventCb(int fd, unique_ptr<Object> obj) {
}

void ServerObj::readEventCb(int fd, unique_ptr<Object> obj) {
    this->acceptServer(fd);
}

void ServerObj::exceptEventCb(int fd, unique_ptr<Object> obj) {

}

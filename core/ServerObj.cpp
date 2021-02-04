//
// Created by jaime on 2021/1/29.
//

#include "ServerObj.h"
#include <sys/socket.h>
#include <iostream>
#include "pool/WorkerPool.h"

void ServerObj::acceptServer(int fd) {
    struct sockaddr addr;
    socklen_t len = sizeof(struct sockaddr*);
    auto new_fd = accept(fd,&addr,&len);
    if ( new_fd < 0 ){
        std::cout<<"accept error "<<errno<<std::endl;
        return;
    }
    cout<<"new fd is "<<new_fd<<endl;
    WorkerPool::getInsance()->notiyEventAdd(new_fd);
}

void ServerObj::writeEventCb(int fd, unique_ptr<Object> obj) {
}

void ServerObj::readEventCb(int fd, unique_ptr<Object> obj) {
    this->acceptServer(fd);
}

void ServerObj::exceptEventCb(int fd, unique_ptr<Object> obj) {

}

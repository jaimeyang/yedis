//
// Created by jaime on 2021/3/20.
//

#include "LinuxStream.h"
#include <sys/socket.h>
#include <iostream>
using namespace std;

void yedis::LinuxStream::inEvent(int fd) {
    auto it = m_bufs.find(fd);
    if (it == this->m_bufs.end()) {
        this->m_bufs[fd] = make_unique<StreamBuf>();
    }
    auto len = 0;
    while ( (len = recv(fd,m_bufs[fd]->write(),m_bufs[fd]->writeAable(),0)) < 0) {
        if (len < -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                continue;
            }
        }
        cout<<"close "<<endl;
        m_bufs[fd].release();
    }
    this->m_bufs[fd]->writeFinish(len);
    this->m_wm->work(m_bufs[fd].get());
}

void yedis::LinuxStream::outEvent(int fd) {
    cout<<"LinuxStream outEvent fd "<<fd<<endl;
}

void yedis::LinuxStream::timeOutEvent(int fd) {
//    IStream::timeOutEvent(fd);
}

void yedis::LinuxStream::errEvent(int fd) {
//    IStream::errEvent(fd);
}
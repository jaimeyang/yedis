//
// Created by jaime on 2021/3/20.
//

#include "LinuxStream.h"
#include <sys/socket.h>
#include <iostream>
#include "NetProxy.h"
using namespace std;

void yedis::LinuxStream::inEvent(int fd) {
    auto it = m_bufs.find(fd);
    if (it == this->m_bufs.end()) {
        this->m_bufs[fd] = make_unique<StreamBuf>();
    }
    auto len = 0;
    //没有数据返回的是-1，并且错误码设置为EAGAIN or EWOULDBLOCK
    //关闭的时候返回0，EOF
    while ( (len = recv(fd,m_bufs[fd]->write(),m_bufs[fd]->writeAable(),0)) != 0) {
        if (len < 0) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                break;
            } else if (errno == EINTR){
                continue;
            } else {
                //出错了
                cout<<"errno"<<errno<<endl;
                break;
            }
        }
        this->m_bufs[fd]->writeFinish(len);
    }
    //关闭了
    if (len == 0) {
        NetProxy::getNproxy()->rmServerFd(fd);
    } else {
        this->m_wm->work(m_bufs[fd].get());
    }

}

void yedis::LinuxStream::outEvent(int fd) {
    cout<<"LinuxStream outEvent fd "<<fd<<endl;
//    char* data = "test";
//    send(fd,data,strlen(data),0);
}

void yedis::LinuxStream::timeOutEvent(int fd) {
//    IStream::timeOutEvent(fd);
}

void yedis::LinuxStream::errEvent(int fd) {
//    IStream::errEvent(fd);
}
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
        this->m_wm->work(m_bufs[fd].get(), this,fd);
    }

}

void yedis::LinuxStream::outEvent(int fd) {
    auto it = this->m_w_buf.find(fd);
    if (it != this->m_w_buf.end()) {
        auto len = this->m_w_buf[fd]->readAble();
        char* ptr = nullptr;
        this->m_w_buf[fd]->read(&ptr,len);
        this->sendNet(fd,ptr,len);
    }
}

void yedis::LinuxStream::timeOutEvent(int fd) {
//    IStream::timeOutEvent(fd);
}

void yedis::LinuxStream::errEvent(int fd) {
//    IStream::errEvent(fd);
}

//尝试发送，如果第一次没有发送出去，则注册到网络的可写事件
void yedis::LinuxStream::writeNet(int fd,unique_ptr<StreamBuf> buf) {
    auto len = buf->readAble();
    char* ptr = nullptr;
    buf->read(&ptr,len);
    auto s_len = this->sendNet(fd,ptr,len);
    if (s_len > 0) {
        buf->readFinish(s_len);
        this->m_w_buf[fd] = std::move(buf);
    }
}

int yedis::LinuxStream::sendNet(int fd, char* data, int len) {
    cout<<"sendNet is "<<data<<endl;
    auto send_len = send(fd,data,len,0);
    auto remain_len = 0;
    if (send_len < 0) {
        if (errno != EWOULDBLOCK) {
            cout<<"send errno "<<errno<<endl;
            return -1;
        }
    } else {
        remain_len = len - send_len;
    }
    if (remain_len > 0) {
        NetProxy::getNproxy()->regSendEvent(this,fd);
    }
    return remain_len;
}


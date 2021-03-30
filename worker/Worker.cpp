//
// Created by jaime on 2021/3/27.
//

#include <iostream>
#include "Worker.h"
#include <string>
#include <cstring>

void yedis::Worker::init() {
#ifdef  LINUX
    this->m_thr = make_unique<LinuxPth>();
#endif
    this->setState(WorkState::IDLE);
    this->m_thr->start([this](void*){
        this->loop();
    });
}

void yedis::Worker::loop() {
    std::unique_lock<std::mutex> lk(this->c_tex);
    while (true) {
        cv.wait(lk);
        this->setState(WorkState::RUNNING);
        auto n = this->m_buf->readAble();
        char* data = nullptr;
        auto len = this->m_buf->read(&data,n);
        cout<<"data is "<<data<<endl;
        //todo add the function of write in the LinuxStream,first,to write the data in direct
        //if cannot write the data,register the write event,
        auto resp = std::make_unique<StreamBuf>();
        const char* resp_data = "sssdfds";
        memcpy(resp->write(),resp_data,strlen(resp_data));
        this->m_net->writeNet(this->m_fd,std::move(resp));
        this->setState(WorkState::IDLE);
    }
}

void yedis::Worker::notify() {
    cv.notify_one();
}

void yedis::Worker::work(yedis::StreamBuf* buf,INetEvent* net,int fd) {
    this->m_buf = buf;
    this->m_net = net;
    this->m_fd = fd;
}
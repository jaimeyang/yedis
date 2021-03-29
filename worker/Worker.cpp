//
// Created by jaime on 2021/3/27.
//

#include <iostream>
#include "Worker.h"

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
        cout<<"await"<<endl;
        this->setState(WorkState::RUNNING);
        auto n = this->m_buf->readAble();
        cout<<"n is "<<n<<endl;
        char* data = nullptr;
        auto len = this->m_buf->read(&data,n);
        cout<<"data is "<<data<<endl;
        cout<<"len is "<<len<<endl;
        this->setState(WorkState::IDLE);
        //todo add the function of write in the LinuxStream,first,to write the data in direct
        //if cannot write the data,register the write event,
    }
}

void yedis::Worker::notify() {
    cv.notify_one();
}

void yedis::Worker::work(yedis::StreamBuf* buf) {
    this->m_buf = buf;
}
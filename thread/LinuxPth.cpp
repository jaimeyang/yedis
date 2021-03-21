//
// Created by jaime on 2021/3/20.
//

#include "LinuxPth.h"
#include <iostream>
#include <cstring>

void* thr_run(void* data) {
    auto pth = (yedis::LinuxPth*)data;
    pth->callfunc();
    return nullptr;
}


void yedis::LinuxPth::start(function<void(void*)>func,void* data) {
    this->m_func = func;
    this->m_data = data;
    auto err = pthread_create(&this->m_pid, nullptr, thr_run,(void*)this);
    if (err != 0) {
        cout<<"linux pthread create err "<<strerror(err)<<endl;
        return;
    }
    pthread_detach(this->m_pid);
}

void yedis::LinuxPth::stop() {

}

void yedis::LinuxPth::await() {

}

void yedis::LinuxPth::callfunc() {
    this->m_func(this->m_data);
}

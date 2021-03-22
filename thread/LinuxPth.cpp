//
// Created by jaime on 2021/3/20.
//

#include "LinuxPth.h"
#include <iostream>
#include <cstring>
#include <zconf.h>

using ThredData = struct {
    function<void(void*)> func;
    void* data;
};

void* thr_run(void* data) {
    auto t_data = (ThredData*)data;
    t_data->func(data);
    delete t_data->data;
    t_data->data = nullptr;
    delete t_data;
    t_data = nullptr;
    return nullptr;
}

ThredData* makeThredData(function<void(void*)> func,void* data) {
    auto ret = new ThredData();
    ret->func = func;
    ret->data = data;
    return ret;
}


void yedis::LinuxPth::start(function<void(void*)> func,void* data) {
    auto t_data = makeThredData(func,data);
    pthread_t t;
    auto err = pthread_create(&t, nullptr,thr_run, (void*)t_data);
    if (err != 0) {
        cout<<"linux pthread create err "<<strerror(err)<<endl;
        return;
    }
    pthread_detach(t);
}

void yedis::LinuxPth::stop() {

}

void yedis::LinuxPth::await() {

}

void yedis::LinuxPth::callfunc() {
    this->m_func(this->m_data);
}

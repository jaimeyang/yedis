//
// Created by jaime on 2021/3/27.
//

#include "StreamBuf.h"
#include <iostream>

int yedis::StreamBuf::read(char* data,int n) {
    if (this->readAble() == 0) {
        data = nullptr;
        return 0;
    }
    data = this->m_data.data() + this->m_r_index;
    if (n > this->readAble()) {
        return this->readAble();
    }
    return n;
}

void yedis::StreamBuf::readFinish(int n) {
    if (n > this->readAble()) {
        return;
    }
    this->m_r_index = (this->m_r_index + n) % this->m_data.capacity();
}

void yedis::StreamBuf::writeFinish(int n) {
    if (n > this->writeAable()) {
        return;
    }
    this->m_w_index = (this->m_w_index + n) % this->m_data.capacity();
}


//
// Created by jaime on 2021/3/27.
//

#include "Wmanager.h"

void yedis::Wmanager::createPool(int num) {
    for (int i = 0; i < num; ++i) {
        auto w = make_unique<Worker>();
        w->init();
        this->m_idle.push(std::move(w));
    }
}

void yedis::Wmanager::work(StreamBuf* buf,INetEvent* net,int fd) {
//    if (this->m_idle.size() > 0) {
//        while (this->m_idle.size() > 0) {
//            if (this->m_idle.front()->getState() == WorkState::RUNNING) {
//                this->m_running.push(std::move(this->m_idle.front()));
//                this->m_idle.pop();
//            } else {
//                this->m_idle.front()->work(buf,net,fd);
//            }
//        }
//    }

}

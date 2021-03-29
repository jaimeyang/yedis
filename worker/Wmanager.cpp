//
// Created by jaime on 2021/3/27.
//

#include "Wmanager.h"

void yedis::Wmanager::createPool(int num) {
    this->m_idle.reserve(num);
    this->m_running.reserve(num);
    for (int i = 0; i < num; ++i) {
        auto worker = make_unique<Worker>();
        worker->init();
        this->m_idle.push_back(std::move(worker));
    }
}

void yedis::Wmanager::work(StreamBuf* buf) {
    if (this->m_idle.size() > 0) {
        while (this->m_idle.front()->getState() == WorkState::RUNNING) {
            auto it = this->m_idle.begin();
            this->m_running.push_back(std::move(this->m_idle.front()));
            this->m_idle.erase(it);
        }
        this->m_idle.front()->work(buf);
        this->m_idle.front()->notify();
    } else {
        auto it = this->m_running.begin();
        auto i = 0;
        while (it != this->m_running.end()) {
            if ((*it)->getState() == WorkState::IDLE) {
                if (i == 0) {
                    (*it)->work(buf);
                    (*it)->notify();
                } else {
                    this->m_idle.push_back(std::move((*it)));
                    it = this->m_idle.erase(it);
                }
                i++;
            }
        }
        //todo i == 0 no enough worker,must create the new worker
//        if (i == 0) {
//            auto worker = make_unique<Worker>();
//            worker->init();
//        }
    }
}

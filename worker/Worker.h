//
// Created by jaime on 2021/3/27.
//

#ifndef YEDIS_WORKER_H
#define YEDIS_WORKER_H

#include "StreamBuf.h"
#include <memory>
#include <condition_variable>
#include "INetEvent.h"

#ifdef LINUX
#include "LinuxPth.h"
#endif


using namespace std;

namespace yedis {
    class Wmanager;
    enum WorkState {
        IDLE = 0,
        RUNNING = 1,
    };
    class Worker {
    public:
        void init();
        WorkState getState() {
            return this->m_state;
        }
        void setState(WorkState state) {
            this->m_state = state;
        }
        void loop();
        void notify();
        void work(StreamBuf* buf,INetEvent* net,int fd);
    private:
        StreamBuf* m_buf = nullptr;
        WorkState m_state;
        unique_ptr<IThread> m_thr;
        condition_variable cv;
        mutex c_tex;
        INetEvent* m_net;
        int m_fd;
    };
}




#endif //YEDIS_WORKER_H

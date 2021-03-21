//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_EPOLL_H
#define YEDIS_EPOLL_H

#include "IMultiIo.h"

using namespace std;

namespace yedis {
    class Epoll final : public IMultiIo {
    public:
        ~Epoll() = default;
        void init() override;
        void addFd(int fd) override;
        void rmFd(int fd) override;
        void regEvent(INetEvent* event) override;
        void loop() override;
    public:
        int m_ep_fd = 0;
        int m_max_events = 1024;
    };
}




#endif //YEDIS_EPOLL_H

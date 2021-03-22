//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_EPOLL_H
#define YEDIS_EPOLL_H

#include "IMultiIo.h"
#include "StreamListen.h"
#include <memory>
#include <unordered_map>

using namespace std;

namespace yedis {
    class Epoll final : public IMultiIo {
    public:
        ~Epoll() = default;
        void init() override;
        void bindNevent(unique_ptr<INetEvent> event) override;
        void addFd(int fd) override;
        void rmFd(int fd) override;
        void regEvent(INetEvent* event,int fd) override;
        void loop() override;
    private:
    private:
        int m_ep_fd = 0;
        int m_max_events = 1024;
        unique_ptr<INetEvent> m_stram;
        unordered_map<int,INetEvent*> m_events;
    };
}




#endif //YEDIS_EPOLL_H

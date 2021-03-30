//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_INETEVENT_H
#define YEDIS_INETEVENT_H

#include "memory"
#include "StreamBuf.h"
#include <vector>

using namespace std;

namespace yedis {
    class INetEvent {
    public:
        virtual ~INetEvent() = default;
        virtual void inEvent(int fd) = 0;
        virtual void outEvent(int fd) = 0;
        virtual void timeOutEvent(int fd) = 0;
        virtual void errEvent(int fd) = 0;
        virtual void writeNet(int fd,unique_ptr<StreamBuf> buf) = 0;
    };
}




#endif //YEDIS_INETEVENT_H

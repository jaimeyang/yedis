//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_INETEVENT_H
#define YEDIS_INETEVENT_H

namespace yedis {
    class INetEvent {
    public:
        virtual ~INetEvent() = default;
        virtual int getfd() = 0;
        virtual void inEvent() = 0;
        virtual void outEvent() = 0;
        virtual void timeOutEvent() = 0;
        virtual void errEvent() = 0;
    };
}




#endif //YEDIS_INETEVENT_H

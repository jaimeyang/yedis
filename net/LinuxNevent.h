//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_LINUXNEVENT_H
#define YEDIS_LINUXNEVENT_H

#include "INetEvent.h"

namespace yedis {
    class LinuxNevent : public INetEvent {
    public:
        ~LinuxNevent() {

        }
        void inEvent() override;
        void outEvent() override;
        void timeOutEvent() override;
    };

}


#endif //YEDIS_LINUXNEVENT_H

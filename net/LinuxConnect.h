//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_LINUXCONNECT_H
#define YEDIS_LINUXCONNECT_H

#include "StreamConnect.h"

namespace yedis {
    class LinuxConnect : public StreamConnect {
    public:
        ~LinuxConnect() = default;
        void connect(const string &addr) override;
    };
}




#endif //YEDIS_LINUXCONNECT_H

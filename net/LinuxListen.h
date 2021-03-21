//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_LINUXLISTEN_H
#define YEDIS_LINUXLISTEN_H

#include "StreamListen.h"

namespace yedis {
    class LinuxListen : public StreamListen{
    public:
        ~LinuxListen() = default;
        void listenServer(const string& addr,int port) override;
        void acceptServer(int fd);
    };

}



#endif //YEDIS_LINUXLISTEN_H

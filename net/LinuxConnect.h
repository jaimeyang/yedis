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
        int connectServer(const string &addr,int port) override;

    private:
        int createSocket();

    private:
        int m_fd;
    };
}




#endif //YEDIS_LINUXCONNECT_H

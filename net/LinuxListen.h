//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_LINUXLISTEN_H
#define YEDIS_LINUXLISTEN_H

#include "StreamListen.h"
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include <arpa/inet.h>
#include <cstring>

namespace yedis {
    class LinuxListen : public StreamListen{
    public:
        ~LinuxListen() = default;
        void bindMIo(IMultiIo *io) override;
        void listenServer(const string& addr,int port) override;
    private:
        void acceptServer(int fd,sockaddr_in addr,socklen_t* len);
    private:
        IMultiIo* m_io;
    };

}



#endif //YEDIS_LINUXLISTEN_H

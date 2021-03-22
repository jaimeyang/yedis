//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_LINUXSTREAM_H
#define YEDIS_LINUXSTREAM_H
#include "IStream.h"

namespace yedis {
    class LinuxStream : public INetEvent {
    public:
        ~LinuxStream() {

        }
        void inEvent(int fd) override;
        void outEvent(int fd) override;
        void timeOutEvent(int fd) override;
        void errEvent(int fd) override;
//        int tcpRead(vector<Msg> &msgs) override;
//        int tcpWrite(vector<Msg> &msgs) override;
    };
}




#endif //YEDIS_LINUXSTREAM_H

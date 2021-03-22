//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_ISTREAM_H
#define YEDIS_ISTREAM_H

#include "Msg.h"
#include "INetEvent.h"

namespace yedis {
    class IStream : public INetEvent  {
    public:
        virtual  ~IStream() = default;
        virtual int tcpRead(vector<Msg>& msgs) = 0;
        virtual int tcpWrite(vector<Msg>& msgs) = 0;
    };
}




#endif //YEDIS_ISTREAM_H

//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_ISTREAM_H
#define YEDIS_ISTREAM_H

#include "Msg.h"

namespace yedis {
    class IStream {
    public:
        virtual  ~IStream() = default;
        virtual int read(vector<Msg>& msgs) = 0;
        virtual int write(vector<Msg>& msgs) = 0;
    };
}




#endif //YEDIS_ISTREAM_H

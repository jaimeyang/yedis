//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_LINUXSTREAM_H
#define YEDIS_LINUXSTREAM_H
#include "IStream.h"

namespace yedis {
    class LinuxStream : public IStream {
    public:
        ~LinuxStream() {

        }
        int read(vector<Msg> &msgs) override;
        int write(vector<Msg> &msgs) override;
    };
}




#endif //YEDIS_LINUXSTREAM_H

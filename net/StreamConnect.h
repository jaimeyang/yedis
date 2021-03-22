//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_STREAMCONNECT_H
#define YEDIS_STREAMCONNECT_H

#include <string>

using namespace std;

namespace yedis {
    class StreamConnect {
    public:
        virtual ~StreamConnect() = default;
        virtual int connectServer(const string& addr,int port) = 0;
    };

}



#endif //YEDIS_STREAMCONNECT_H

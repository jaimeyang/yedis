//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_STREAMLISTEN_H
#define YEDIS_STREAMLISTEN_H

#include <string>
#include "IMultiIo.h"

using namespace std;
namespace yedis {
    class StreamListen {
    public:
        virtual ~StreamListen() = default;
        virtual void bindMIo(IMultiIo* io) = 0;
        virtual void listenServer(const string& addr,int port) = 0;
    };
}


#endif //YEDIS_STREAMLISTEN_H

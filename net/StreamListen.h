//
// Created by jaime on 2021/3/21.
//

#ifndef YEDIS_STREAMLISTEN_H
#define YEDIS_STREAMLISTEN_H

#include <string>

using namespace std;
namespace yedis {
    class StreamListen {
    public:
        virtual ~StreamListen() = default;
        virtual void listenServer(const string& addr,int port) = 0;
    };
}


#endif //YEDIS_STREAMLISTEN_H

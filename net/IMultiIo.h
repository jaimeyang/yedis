//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_IMULTIIO_H
#define YEDIS_IMULTIIO_H
#include "INetEvent.h"
#include <memory>

using namespace std;

namespace yedis {
    class IMultiIo {
    public:
        virtual ~IMultiIo() = default;
        virtual void init() = 0;
        virtual void bindNevent(unique_ptr<INetEvent> event) = 0;
        virtual void addFd(int fd) = 0;
        virtual void rmFd(int fd) = 0;
        virtual void regEvent(INetEvent* event,int fd) = 0;
        virtual void loop() = 0;

    private:
    };
}




#endif //YEDIS_IMULTIIO_H

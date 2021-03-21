//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_ITHREAD_H
#define YEDIS_ITHREAD_H

#include <functional>

using namespace std;

namespace yedis {
    class IThread {
    public:
        virtual ~IThread() = default;
        virtual void start(function<void(void*)>func,void* data = nullptr) = 0;
        virtual void stop() = 0;
        virtual void await() = 0;
    };

}



#endif //YEDIS_ITHREAD_H

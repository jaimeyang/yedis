//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_LINUXPTH_H
#define YEDIS_LINUXPTH_H

#include "IThread.h"
#include <pthread.h>

namespace yedis {
    class LinuxPth : public IThread {
    public:
        void start(function<void(void*)>func,void* data = nullptr) override;
        void stop() override;
        void await() override;
        void callfunc();
    private:
        function<void(void*)> m_func;
        void* m_data = nullptr;
    };
}



#endif //YEDIS_LINUXPTH_H

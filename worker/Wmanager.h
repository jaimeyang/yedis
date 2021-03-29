//
// Created by jaime on 2021/3/27.
//

#ifndef YEDIS_WMANAGER_H
#define YEDIS_WMANAGER_H

#include "Worker.h"
#include <memory>

using namespace std;

namespace yedis {
    class Wmanager {
    public:
        void createPool(int num);
        void work(StreamBuf* buf);

    private:
        vector<unique_ptr<Worker>> m_running;
        vector<unique_ptr<Worker>> m_idle;
    };

}



#endif //YEDIS_WMANAGER_H

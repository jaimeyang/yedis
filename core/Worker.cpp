//
// Created by jaime on 2021/1/30.
//

#include "Worker.h"

void Worker::run() {
    this->m_distpacher = std::make_unique<EpollDispatcher>();
    this->m_distpacher->initDispatch();
    while ( true ) {

        this->m_distpacher->disPatch();
    }
}

//
// Created by jaime on 2021/3/30.
//

#ifndef YEDIS_PARAMS_H
#define YEDIS_PARAMS_H

#endif //YEDIS_PARAMS_H

namespace yedis {
#if EPOLL
#include <sys/epoll.h>
    using POLL_EVENT = uint32_t;
    enum POLLEVENTS {
        POLL_IN = EPOLLIN,
        POLL_OUT = EPOLLOUT,
        POLL_ET = EPOLLET,
        POLL_ERROR = EPOLLERR,
    };
#endif
}


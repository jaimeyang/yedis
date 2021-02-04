//
// Created by jaime on 2021/2/4.
//

#ifndef YEDIS_TCPEVENTOBJ_H
#define YEDIS_TCPEVENTOBJ_H

#include "Object.h"

class TcpEventObj : public Object{
public:
    virtual void readEventCb(int fd,unique_ptr<Object> obj) = 0;
    virtual void writeEventCb(int fd,unique_ptr<Object> obj) = 0;
    virtual void exceptEventCb(int fd,unique_ptr<Object> obj) = 0;
};

#endif //YEDIS_TCPEVENTOBJ_H

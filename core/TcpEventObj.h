//
// Created by jaime on 2021/2/4.
//TCP事件的回调接口

#ifndef YEDIS_TCPEVENTOBJ_H
#define YEDIS_TCPEVENTOBJ_H

#include "Object.h"

class TcpEventObj : public Object{
public:
    //读事件回调
    virtual void readEventCb(int fd,unique_ptr<Object> obj) = 0;
    //写事件回调
    virtual void writeEventCb(int fd,unique_ptr<Object> obj) = 0;
    //异常事件回调
    virtual void exceptEventCb(int fd,unique_ptr<Object> obj) = 0;
};

#endif //YEDIS_TCPEVENTOBJ_H

//
// Created by jaime on 2021/1/29.
//

#ifndef ROBOT_SERVEROBJ_H
#define ROBOT_SERVEROBJ_H


#include "TcpEventObj.h"

class ServerObj: public TcpEventObj {
public:
    void writeEventCb(int fd, unique_ptr<Object> obj) override;
    void readEventCb(int fd, unique_ptr<Object> obj) override;
    void exceptEventCb(int fd, unique_ptr<Object> obj) override;

public:
    void acceptServer(int fd);
};


#endif //ROBOT_SERVEROBJ_H

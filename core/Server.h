//
// Created by jaime on 2021/1/28.
//主线程的实现，负责接受新连接，已经通过socketpair把需要读写的文件描述符传递给子线程

#ifndef ROBOT_SERVER_H
#define ROBOT_SERVER_H

#include <memory>
#include "EpollDispatcher.h"

using namespace std;

class Server{
public:
    Server():
    m_dispatch(make_unique<EpollDispatcher>()){

    }
    ~Server(){

    }
    void listenServer();


    //主循环
    void runServer();
public:
    int m_lifd;
    unique_ptr<Distpacher> m_dispatch;
};


#endif //ROBOT_SERVER_H

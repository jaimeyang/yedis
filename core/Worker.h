//
// Created by jaime on 2021/1/30.
//工作的子线程，负责读写

#ifndef ROBOT_WORKER_H
#define ROBOT_WORKER_H
#include "Object.h"
#include "EpollDispatcher.h"
#include <memory>

using namespace std;

class Worker{
public:
    Worker(int fd):
    m_fd(fd){

    }
    ~Worker(){

    }
public:
    void run();

private:
    shared_ptr<Distpacher> m_distpacher;
    int m_fd;
};


#endif //ROBOT_WORKER_H

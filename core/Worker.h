//
// Created by jaime on 2021/1/30.
//

#ifndef ROBOT_WORKER_H
#define ROBOT_WORKER_H
#include "Object.h"
#include "EpollDispatcher.h"
#include <memory>

using namespace std;

class Worker : public Object {
public:
    Worker(){

    }
    ~Worker(){

    }
public:
    void run();

private:
    unique_ptr<Distpacher> m_distpacher;
};


#endif //ROBOT_WORKER_H

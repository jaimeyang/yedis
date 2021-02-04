//
// Created by jaime on 2021/1/29.
//事件分发器的抽象，后续可能添加select,kqueue的支持

#ifndef ROBOT_DISTPACHER_H
#define ROBOT_DISTPACHER_H

#include <memory>
#include "Event.h"

using namespace std;

class Distpacher {
public:
    virtual void initDispatch() = 0;
    virtual void disPatch() = 0;
    virtual void addEvent(unique_ptr<Event> event) = 0;
};


#endif //ROBOT_DISTPACHER_H

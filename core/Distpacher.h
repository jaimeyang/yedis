//
// Created by jaime on 2021/1/29.
//

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

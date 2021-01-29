//
// Created by jaime on 2021/1/29.
//工厂模式创建事件对象
//

#ifndef ROBOT_EVENTFACTORY_H
#define ROBOT_EVENTFACTORY_H


#include <memory>
#include "Event.h"

using namespace std;

class EventFactory {
private:
    EventFactory(){

    }

    ~EventFactory(){

    }

public:
    static EventFactory* create(){
        if ( m_factory == nullptr ){
            m_factory = new EventFactory();
        }
        return m_factory;
    }
    unique_ptr<Event> createEvent(EventType type,int fd,EventCallback cb,void* data);
private:
    static EventFactory* m_factory;
};


#endif //ROBOT_EVENTFACTORY_H

//
// Created by jaime on 2021/1/29.
//

#include "EventFactory.h"

EventFactory* EventFactory::m_factory = nullptr;

unique_ptr<Event> EventFactory::createEvent(EventType type,int fd,unique_ptr<TcpEventObj> obj,unique_ptr<Object> data) {
    unique_ptr<Event> e = make_unique<Event>(type,fd,std::move(obj),std::move(data));
    return std::move(e);
}

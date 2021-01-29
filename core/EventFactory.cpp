//
// Created by jaime on 2021/1/29.
//

#include "EventFactory.h"

unique_ptr<Event> EventFactory::createEvent(EventType type,int fd, EventCallback cb, void *data) {
    unique_ptr<Event> e = make_unique<Event>(type,fd,cb,data);
    return std::move(e);
}

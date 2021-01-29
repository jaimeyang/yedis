//
// Created by jaime on 2021/1/28.
//

#ifndef ROBOT_EVENT_H
#define ROBOT_EVENT_H
#include <sys/epoll.h>
#include <memory>
#include <iostream>

using namespace std;

using EventCallback = void (*)(int fd);

enum EventType{
    READ_EVENT = 0,
    WRITE_EVENT,
    TIMER_EVENT,
};

class Event {
public:
    Event(EventType type,int fd,EventCallback cb,void* data):
    m_type(type),m_fd(fd),m_callback(cb),m_data(data)
    {

    }
    ~Event(){
        std::cout<<"del event"<<std::endl;
    }

public:
    auto getFd(){
        return this->m_fd;
    }

    auto getEpollEvent(){
        auto event = make_unique<epoll_event>();
        event->events = EPOLLIN || EPOLLOUT || EPOLLHUP;
        event->data.ptr = this->m_data;
        return std::move(event);
    }
public:

private:
    int m_fd = -1;
    EventCallback m_callback = nullptr;
    EventType m_type = EventType::READ_EVENT;
    void* m_data = nullptr;
};


#endif //ROBOT_EVENT_H

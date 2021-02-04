//
// Created by jaime on 2021/1/28.
//

#ifndef ROBOT_EVENT_H
#define ROBOT_EVENT_H
#include <sys/epoll.h>
#include <memory>
#include <iostream>
#include "TcpEventObj.h"
#include <unordered_map>

using namespace std;


enum EventType{
    READ_EVENT = 0,
    WRITE_EVENT,
    TIMER_EVENT,
};

class Event {
public:
    Event(EventType type,int fd,unique_ptr<TcpEventObj> obj,unique_ptr<Object> data):
    m_type(type),m_fd(fd),m_obj(std::move(obj)),m_data(std::move(data))
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
        epoll_event event;
        event.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLET;
        event.data.fd = this->m_fd;
        return event;
    }

    void readCb(){
        m_obj.get()->readEventCb(this->m_fd,std::move(this->m_data));
    }

    void writeCb(){
        m_obj.get()->writeEventCb(this->m_fd,std::move(this->m_data));
    }

    void exceCb(){
        m_obj.get()->exceptEventCb(this->m_fd,std::move(this->m_data));
    }
public:

private:
    int m_fd = -1;
    EventType m_type = EventType::READ_EVENT;
    unique_ptr<TcpEventObj> m_obj;
    unique_ptr<Object> m_data;
};


#endif //ROBOT_EVENT_H

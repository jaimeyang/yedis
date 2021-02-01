//
// Created by jaime on 2021/1/29.
//

#include "EpollDispatcher.h"
#include <sys/epoll.h>
#include <iostream>

void EpollDispatcher::initDispatch() {
    this->m_epoll_fd = epoll_create(1);
    if ( this->m_epoll_fd < 0 ){
        std::cout<<"epoll_create rror"<<errno<<std::endl;
        return;
    }
    this->events = new epoll_event[1024];
}

void EpollDispatcher::disPatch() {
    int maxevnt = 1024;
    int n = epoll_wait(this->m_epoll_fd,this->events,maxevnt,1);
    for (int i = 0; i < n; ++i) {
        auto ep_event = events[i];
        if ( this->m_event_map.find(ep_event.data.fd) == this->m_event_map.end() ){
            continue;
        }
        auto event = std::move(this->m_event_map.at(ep_event.data.fd));
        //可读
        if ( ep_event.events & EPOLLIN ){
            event->readCb();
        }
        //可写
        if ( ep_event.events & EPOLLOUT ){
            std::cout<<"new write"<<std::endl;
        }
        //关闭
        if ( (ep_event.events & EPOLLHUP) || (ep_event.events & EPOLLERR)){
            std::cout<<"new error"<<std::endl;
        }
        this->m_event_map[ep_event.data.fd] = std::move(event);
    }
}

void EpollDispatcher::addEvent(unique_ptr<Event> event) {
    epoll_event ev = event->getEpollEvent();
    auto ret = epoll_ctl(this->m_epoll_fd,EPOLL_CTL_ADD,event->getFd(),&ev);
    if ( ret < 0 ){
        std::cout<<"epoll_crl errno "<<errno<<std::endl;
        return;
    }
    this->m_event_map[event->getFd()] = std::move(event);
}

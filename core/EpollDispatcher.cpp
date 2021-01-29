//
// Created by jaime on 2021/1/29.
//

#include "EpollDispatcher.h"
#include <sys/epoll.h>
#include <iostream>

void EpollDispatcher::initDispatch() {
    this->m_epoll_fd = epoll_create(65535);
    if ( this->m_epoll_fd < 0 ){
        std::cout<<"epoll_create rror"<<errno<<std::endl;
        return;
    }

}

void EpollDispatcher::disPatch() {

}

void EpollDispatcher::addEvent(unique_ptr<Event> event) {
    auto ret = epoll_ctl(this->m_epoll_fd,EPOLL_CTL_ADD,event->getFd(),event->getEpollEvent().get());
    if ( ret < 0 ){
        std::cout<<"epoll_crl errno "<<errno<<std::endl;
        return;
    }

}

//
// Created by jaime on 2021/3/20.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <iostream>
#include <cstring>
#include "LinuxStream.h"

void yedis::Epoll::init() {
    this->m_ep_fd = epoll_create(1);
    if (this->m_ep_fd < 0) {
        cout<<"eopll create fail "<<strerror(errno)<<endl;
        return;
    }
}

void yedis::Epoll::bindNevent(unique_ptr<INetEvent> event) {
    this->m_stram = std::move(event);
}


void yedis::Epoll::addFd(int fd) {
    auto event = new epoll_event();
    event->events = EPOLLIN | EPOLLOUT | EPOLLERR;
    event->data.fd = fd;
    auto err = 0;
    try {
        err = epoll_ctl(this->m_ep_fd,EPOLL_CTL_ADD,fd,event);
    } catch (...) {
        if (err != 0) {
            cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
            return;
        }
    }

}

void yedis::Epoll::rmFd(int fd) {
    auto err = 0;
    try {
        err = epoll_ctl(this->m_ep_fd,EPOLL_CTL_DEL,fd, nullptr);
    } catch (...) {
        if (err != 0) {
            cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
            return;
        }
    }
}

void yedis::Epoll::regEvent(INetEvent* netev,int fd) {
//    auto efd = f
    auto event = new epoll_event();
    event->events = EPOLLIN | EPOLLOUT | EPOLLERR;
    event->data.fd = fd;
    auto err = 0;
    try {
        err = epoll_ctl(this->m_ep_fd,EPOLLIN,fd, event);
    } catch (...) {
        delete netev;
        netev = nullptr;
        if (err != 0) {
            cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
            return;
        }
    }
    this->m_events[fd] = netev;
}

void yedis::Epoll::loop() {
    auto events = new epoll_event[this->m_max_events];
    while (true) {
        int n = epoll_wait(this->m_ep_fd,events,this->m_max_events,1);
        for (int i = 0; i < n; ++i) {
            auto ep_event = events[i];
            auto fd = events[i].data.fd;
            auto e_it = this->m_events.find(fd);
            if (e_it != this->m_events.end()) {
                auto event = this->m_events[fd];
                if (ep_event.events & EPOLLIN) {
                    event->inEvent(fd);
                }
                if (ep_event.events & EPOLLOUT) {
                    event->outEvent(fd);
                }
                if (ep_event.events & EPOLLERR) {
                    event->errEvent(fd);
                }
            } else {
                //                auto event = (INetEvent*)ep_event.data.ptr;
                if (ep_event.events & EPOLLIN) {
                    this->m_stram->inEvent(fd);
                }
                if (ep_event.events & EPOLLOUT) {
                    this->m_stram->outEvent(fd);
                }
                if (ep_event.events & EPOLLERR) {
                    this->m_stram->errEvent(fd);
                }
            }

        }
    }
}







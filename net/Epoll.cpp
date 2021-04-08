//
// Created by jaime on 2021/3/20.
//

#include "Epoll.h"
#include <sys/epoll.h>
#include <iostream>
#include <cstring>
#include "LinuxStream.h"
#include <sys/socket.h>
#include <unistd.h>



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
//    event->events = EPOLLIN | EPOLLOUT | EPOLLERR | EPOLLET;
    event->events = POLL_IN | POLL_OUT | POLL_ERROR | POLL_ET;
    event->data.fd = fd;
    auto err = epoll_ctl(this->m_ep_fd,EPOLL_CTL_ADD,fd,event);
    if (err != 0) {
        cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
        return;
    }
}

void yedis::Epoll::rmFd(int fd) {
    auto err = epoll_ctl(this->m_ep_fd,EPOLL_CTL_DEL,fd, nullptr);
    if (err != 0) {
        cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
        return;
    }
    //todo use the correct method to close the net
    close(fd);
}

void yedis::Epoll::regEvent(INetEvent* netev,int fd,POLL_EVENT pollevent) {
//    auto efd = f
    auto event = new epoll_event();
    event->events = pollevent;
    event->data.fd = fd;
    auto err = epoll_ctl(this->m_ep_fd,EPOLLIN,fd, event);
    if (err != 0) {
        cout<<"epoll_add error "<<strerror(errno)<<" and fd is "<<fd<<endl;
        delete netev;
        netev = nullptr;
        return;
    }
    this->m_events[fd] = netev;
}

void yedis::Epoll::loop() {
    auto events = new epoll_event[this->m_max_events];
    while (true) {
        int n = epoll_wait(this->m_ep_fd,events,this->m_max_events,1);
        if (n < 0) {
            if (errno == EINTR) {
                continue;
            } else {
                cout<<"epoll wait errno"<<errno<<endl;
                break;
            }
        }
        for (int i = 0; i < n; ++i) {
            auto ep_event = events[i];
            auto fd = events[i].data.fd;
            auto e_it = this->m_events.find(fd);
            if (e_it != this->m_events.end()) {
                auto event = this->m_events[fd];
                if (ep_event.events & POLL_IN) {
                    event->inEvent(fd);
                }
                if (ep_event.events & POLL_OUT) {
                    event->outEvent(fd);
                }
                if (ep_event.events & POLL_ERROR) {
                    cout<<"errno is "<<strerror(errno)<<endl;
                    event->errEvent(fd);
                }
            } else {
                if (ep_event.events & POLL_IN) {
                    this->m_stram->inEvent(fd);
                }
                if (ep_event.events & POLL_OUT) {
                    this->m_stram->outEvent(fd);
                }
                if (ep_event.events & POLL_ERROR) {
                    this->m_stram->errEvent(fd);
                }
            }

        }
    }
}







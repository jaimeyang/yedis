//
// Created by jaime on 2021/3/20.
//

#include <iostream>
#include "NetProxy.h"

yedis::NetProxy* yedis::NetProxy::m_proxy = nullptr;

void yedis::NetProxy::initNet() {
    this->m_io->init();
}

void yedis::NetProxy::addFd(int fd) {
    this->m_io->addFd(fd);
}

void yedis::NetProxy::rmFd(int fd) {
    this->m_io->rmFd(fd);
}

void yedis::NetProxy::regEvent(INetEvent* event) {
//    this->m_io->regEvent(event);
}

void yedis::NetProxy::startClient() {
    this->m_thr->start([this](void*){
        m_cio->init();
        m_cio->loop();
        }, nullptr);
}

void yedis::NetProxy::startServer(const string &addr,int port) {

    this->m_thr->start([this](void*){
#ifdef LINUX
        auto stream = make_unique<LinuxStream>();
#endif
        m_io->init();
        m_io->bindNevent(std::move(stream));
        m_io->loop();
    }, nullptr);
    this->m_thr->start([this,addr,port](void*){
        this->m_server->bindMIo(m_io.get());
        this->m_server->listenServer(addr,port);
    }, nullptr);
}

int yedis::NetProxy::connect(const string &addr,int port,INetEvent* netEvent) {
#ifdef LINUX
    auto c = make_unique<LinuxConnect>();
    auto fd = c->connectServer(addr,port);
#endif
    auto poll_ev = POLL_OUT | POLL_ERROR | POLL_ET;
    this->m_cio->regEvent(netEvent,fd,poll_ev);
    return fd;
}

void yedis::NetProxy::closeClient(int fd) {
    this->m_cio->rmFd(fd);
}

void yedis::NetProxy::rmServerFd(int fd) {
    this->m_io->rmFd(fd);
}

void yedis::NetProxy::regSendEvent(yedis::INetEvent* event, int fd) {
    auto poll_event = POLL_OUT | POLL_ERROR | POLL_ET;
    this->m_io->regEvent(event,fd,poll_event);
}





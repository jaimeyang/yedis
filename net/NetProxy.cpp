//
// Created by jaime on 2021/3/20.
//

#include "NetProxy.h"

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

void yedis::NetProxy::startServer(const string &addr,int port) {
    this->m_thr->start([this](void*){
#ifdef LINUX
        auto stream = make_unique<LinuxStream>();
#endif
        m_io->bindNevent(std::move(stream));
        m_io->loop();
    }, nullptr);
    this->m_server->listenServer(addr,port);
}

void yedis::NetProxy::connect(const string &addr,int port) {

}



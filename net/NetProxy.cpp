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
    this->m_io->regEvent(event);
}

void yedis::NetProxy::startServer(const string &addr) {
    this->m_server->listen(addr);
}

void yedis::NetProxy::connect(const string &addr) {

}



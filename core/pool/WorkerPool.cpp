//
// Created by jaime on 2021/2/3.
//

#include "WorkerPool.h"
#include "../Worker.h"
#include <sys/types.h>
#include <sys/socket.h>

WorkerPool* WorkerPool::m_instance = nullptr;

unique_ptr<array<int,2>> WorkerPool::createSocketPair() {
    int fds[2] = {};
    int result = socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
    if ( result < 0 ){
        std::cout<<"socket pair is "<<errno<<std::endl;
        return nullptr;
    }
    array<int,2> a1 = {fds[0],fds[1]};
    auto uptr = make_unique<array<int,2>>(a1);
    return std::move(uptr);
}

void* run(void* data) {
    int fd = *(int*)data;
    auto work = new Worker(fd);
    work->run();
}

void WorkerPool::createWorker() {
    auto fds = this->createSocketPair();
    this->m_sps[0] = fds.get()->at(0);
    int fd = fds.get()->at(1);
    pthread_t t;
    pthread_create(&t, nullptr,run,&fd);
    pthread_detach(t);
}

void WorkerPool::notiyEventAdd(int newfd) {
    int fd = this->m_sps[0];
    const char* data = to_string(newfd).c_str();
    int ret = send(fd,data,sizeof(data),0);
    cout<<"ret "<<ret<<endl;
}

//
// Created by jaime on 2021/2/4.
//

#include "WorkerObject.h"
#include <sys/socket.h>
#include <iostream>
#include "Interger.h"
#include "EventFactory.h"

void WorkerObject::exceptEventCb(int fd, unique_ptr<Object> obj) {

}

void WorkerObject::readEventCb(int fd, unique_ptr<Object> obj) {
    char* data = new char[1024];
    int ret = recv(fd,(void*)data,1024,0);
    //表示对端已经关闭
    if (ret == 0){
        //todo 正确的关闭方式
    }else{
        if ( obj == nullptr ){
            cout<<"data is "<<data<<endl;
            return;
        }
    }

    //主线程发送过来的,需要加入到子线程监听
    auto cobj = unique_ptr<WorkerObject>(this);
    auto rfd = atoi(data);
    auto event = EventFactory::create()->createEvent(EventType::READ_EVENT,rfd,std::move(cobj), nullptr);
    this->m_dispatcher->addEvent(std::move(event));

}

void WorkerObject::writeEventCb(int fd, unique_ptr<Object> obj) {

}

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
            printf("data is %s\n",data);
            const string_view str(data);
            auto result = m_redis->execCommand(str);
            //写回给客户端
            //todo 一次写可能写不完，以后要加上buffer去处理，包括粘包和半包的问题
            if ( result != nullptr ){
                auto len = result.get()->length();
                int ret = send(fd,result->data(),len,0);
            }

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

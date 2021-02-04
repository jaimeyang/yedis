//
// Created by jaime on 2021/1/28.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include "Server.h"
#include "EventFactory.h"
#include "ServerObj.h"
#include <arpa/inet.h>
#include "pool/WorkerPool.h"
//主线程监听
void Server::listenServer() {
    this->m_lifd = socket(AF_INET,SOCK_STREAM,0);
    if (this->m_lifd < 0){
        std::cout<<"error "<<errno<<std::endl;
        return;

    }
    sockaddr_in addr;
    bzero(&addr,sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(9000);
    addr.sin_addr.s_addr =  inet_addr("0.0.0.0");

    int reuse = 1;
    setsockopt(this->m_lifd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));

    if ( bind(this->m_lifd,(struct sockaddr*)&addr,sizeof(addr)) < 0 ){
        std::cout<<"bind error "<<errno<<std::endl;
        return;
    }

    if ( listen(this->m_lifd,65553) < 0 ){
        std::cout<<"listen error "<<errno<<std::endl;
    }
    std::cout<<"server listen start"<<std::endl;
    auto sobj = make_unique<ServerObj>();
    auto event = EventFactory::create()->createEvent(EventType::READ_EVENT,this->m_lifd,std::move(sobj), nullptr);
    m_dispatch->addEvent(std::move(event));
}
//主线程主循环
void Server::runServer() {
    this->m_dispatch->initDispatch();
    this->listenServer();
    WorkerPool::getInsance()->createWorker();
    while (true){
        m_dispatch->disPatch();
    }
}





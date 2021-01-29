//
// Created by jaime on 2021/1/28.
//

#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <strings.h>
#include "Server.h"
#include "EventFactory.h"
#include <arpa/inet.h>
#include <zconf.h>

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
    if ( bind(this->m_lifd,(struct sockaddr*)&addr,sizeof(addr)) < 0 ){
        std::cout<<"bind error "<<errno<<std::endl;
        return;
    }
    int reuse = 1;
    setsockopt(this->m_lifd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int));
    if ( listen(this->m_lifd,65553) < 0 ){
        std::cout<<"listen error "<<errno<<std::endl;
    }
    std::cout<<"server listen start"<<std::endl;
//    auto event = EventFactory::create()->createEvent(EventType::READ_EVENT)

}

void Server::acceptServer() {
    struct sockaddr addr;
    socklen_t len;
    auto fd = accept(this->m_lifd,&addr,&len);
    if ( fd < -1 ){
        std::cout<<"accept error "<<errno<<std::endl;
        return;
    }

}


void Server::runServer() {
    this->listenServer();
    while (true){

        sleep(1000);
    }
}





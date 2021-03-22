//
// Created by jaime on 2021/3/21.
//

#include "LinuxConnect.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <netinet/tcp.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>


using namespace std;

int yedis::LinuxConnect::connectServer(const string& addr,int port) {
    this->createSocket();
    sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr(addr.c_str());
    s_addr.sin_port = htons(port);
    auto err  = connect(this->m_fd,(struct sockaddr*)&s_addr,sizeof(s_addr));
    if ( err < 0 ){
        if ( errno == EINPROGRESS ){
            return this->m_fd;
        }
        cout<<"connectServer error"<<strerror(errno)<<endl;
        return err;
    }
    return this->m_fd;
}

int yedis::LinuxConnect::createSocket() {
    this->m_fd = socket(AF_INET,SOCK_STREAM,0);
    if (this->m_fd < 0){
        cout<<"linux create socket error "<<strerror(errno)<<endl;
        return -1;
    }
    int flag = 1;
    setsockopt(this->m_fd, IPPROTO_TCP, TCP_NODELAY,(char*)&flag, sizeof(flag));
    fcntl(this->m_fd, F_SETFL, O_NONBLOCK);
    return m_fd;
}

//
// Created by jaime on 2021/3/20.
//

#include "LinuxStream.h"
#include <sys/socket.h>
#include <iostream>
using namespace std;

void yedis::LinuxStream::inEvent(int fd) {
//    IStream::inEvent(fd);
    cout<<"inEvent fd "<<fd<<endl;
    char data[1024];
    auto len = recv(fd,data,1024,0);
    cout<<"data is "<<data<<endl;
}

void yedis::LinuxStream::outEvent(int fd) {
    cout<<"LinuxStream outEvent fd "<<fd<<endl;
}

void yedis::LinuxStream::timeOutEvent(int fd) {
//    IStream::timeOutEvent(fd);
}

void yedis::LinuxStream::errEvent(int fd) {
//    IStream::errEvent(fd);
}

//int yedis::LinuxStream::tcpRead(vector<Msg> &msgs) {
//    return 0;
//}
//
//int yedis::LinuxStream::tcpWrite(vector<Msg> &msgs) {
//    return 0;
//}

//
// Created by jaime on 2021/3/22.
//

#include "TestNet.h"
#include "INetEvent.h"
#include "NetProxy.h"

using namespace yedis;

class TestNevent : public INetEvent {
public:
    void errEvent(int fd) override {
        cout<<"errEvent fd is "<<fd<<endl;
    }

    void timeOutEvent(int fd) override {
        cout<<"timeOutEvent fd is "<<fd<<endl;
    }

    void outEvent(int fd) override {
        char* data = "wokao";
        send(fd,data,strlen(data),0);
    }

    void inEvent(int fd) override {
//        cout<<"inEvent fd is "<<fd<<endl;
    }

    void writeNet(int fd, unique_ptr<StreamBuf> buf) override {

    }
};


TEST_F(TestNet,test_connect) {
    auto proxy = NetProxy::getNproxy();
    proxy->startClient();
    sleep(1);
    string addr("192.168.1.147");
    auto port = 2183;
    proxy->startServer(addr,port);
    sleep(1);
    auto ev = new TestNevent;
    auto fd = proxy->connect(addr,port,ev);
    sleep(1);
//    proxy->closeClient(fd);
//    cout<<"close"<<endl;
    while (true) {
//        cout<<"connect"<<endl;
        sleep(1);
    }
}
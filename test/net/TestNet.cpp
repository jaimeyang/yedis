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
        cout<<" TestNevent outEvent fd is "<<fd<<endl;
    }

    void inEvent(int fd) override {
        cout<<"inEvent fd is "<<fd<<endl;
    }
};


TEST_F(TestNet,test_connect) {
    auto proxy = make_unique<NetProxy>();
    proxy->startClient();
    string addr("192.168.1.147");
    auto port = 2183;
    proxy->startServer(addr,port);
    auto ev = new TestNevent;
    while (true) {
        cout<<"connect"<<endl;
        proxy->connect(addr,port,ev);
        sleep(1);
    }
}
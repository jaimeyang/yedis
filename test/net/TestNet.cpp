//
// Created by jaime on 2021/3/22.
//

#include "TestNet.h"
#include "INetEvent.h"

using namespace yedis;

class TestNevent : public INetEvent {
public:
    void errEvent(int fd) override {

    }

    void timeOutEvent(int fd) override {

    }

    void outEvent(int fd) override {

    }

    void inEvent(int fd) override {

    }
};


TEST_F(TestNet,test_connect) {

}
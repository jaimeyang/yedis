//
// Created by jaime on 2021/3/20.
//

#include "TestPthread.h"

using namespace yedis;

TEST_F(TestPthread,test_create_pth) {
    auto i = 0;
    auto func = [&i](void* data) {
        i++;
    };
    auto pth = make_unique<LinuxPth>();
    pth->start(func);
    sleep(1);
    ASSERT_EQ(i,1);
}
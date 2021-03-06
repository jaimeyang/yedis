//
// Created by jaime on 2021/3/6.
//

#ifndef YEDIS_TESTMEMPOOL_H
#define YEDIS_TESTMEMPOOL_H

#include "gtest/gtest.h"
#include "pool/MemPool.h"
#include <memory>

class TestMemPool : public testing::Test {
public:
    void SetUp() {

    }

    void TestBody() {

    }

    void TearDown() {

    }
};

TEST_F(TestMemPool,test_createPool) {
    auto p = make_unique<MemPool>();
    p->createPool(16 * 1024);
}


#endif //YEDIS_TESTMEMPOOL_H

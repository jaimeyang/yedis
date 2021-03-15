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

TEST_F(TestMemPool,test_posix_alignment) {
    void* p = nullptr;
    auto err = posix_memalign(&p,16,4096);
//    p1.reset(unique_ptr<PoolHead>(p))
    std::cout<<"test err"<<p<<std::endl;
    void* p1 ;
    auto err1 = posix_memalign(&p1,16,4096);
    std::cout<<"test err"<<p1<<std::endl;
}


#endif //YEDIS_TESTMEMPOOL_H

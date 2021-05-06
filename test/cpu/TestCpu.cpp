//
// Created by jaime on 2021/3/5.
//

#include "gtest/gtest.h"
#include "CpuInfo.h"


class TestCpuInfo : public testing::Test {

};


TEST_F(TestCpuInfo,cpuCacheLine){
    int cpu_cache_line = 64;
    ASSERT_EQ(cpu_cache_line,cacheLineSize());
}


// TEST_F(TestCpuInfo,lambda){
//     auto data = 1;
//     auto l = [p = "PI"](){
//         p = "sss";
//     }

// }

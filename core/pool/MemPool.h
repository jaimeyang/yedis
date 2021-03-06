//
// Created by jaime on 2021/2/26.
//

#ifndef YEDIS_MEMPOOL_H
#define YEDIS_MEMPOOL_H

//align the bytes of cpu cacheline
#include <sys/param.h>
#include <memory>
#include <list>
#include <array>
#include "CpuInfo.h"
#define ye_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ye_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

const int YE_POOL_ALIGEMENT = 16;
using namespace std;

using PoolSNode = struct PoolSNode {
    //when failed over fine,the pointer of curchunk refer to next pool node
    int failed;
    u_char* last;
    u_char* end;
    u_char* next;
};
//over 4k
using PoolLNode = struct PoolLNode {
    u_char* end;
    u_char* next;
};

using PoolHead = struct PoolHead {
    PoolSNode current_s;
    PoolLNode current_l;
};



//the pool of memory inorder to increase of efficiency which allocate the memory.
class MemPool {
public:
    MemPool() {

    }

    ~MemPool() {

    }

    void createPool(int size);
    void* allocateMem(int size);
private:
    void initFreeList();

    template<typename T>
    T& align(T& value) {
      auto cache_line = cacheLineSize();
    }
private:
    PoolHead* m_head = nullptr;
    array<u_char*,9> m_free_arr;
};


#endif //YEDIS_MEMPOOL_H

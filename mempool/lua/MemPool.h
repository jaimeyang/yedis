//
// Created by jaime on 2021/3/8.
//

#ifndef ROBOT_MEMPOOL_H
#define ROBOT_MEMPOOL_H

//align the bytes of cpu cacheline
#include <sys/param.h>
#include <memory>
#include <list>
#include <array>
#include "CpuInfo.h"
#include <iostream>
#include <bitset>
#define ye_align(d, a)     (((d) + (a - 1)) & ~(a - 1))
#define ye_align_ptr(p, a)                                                   \
    (u_char *) (((uintptr_t) (p) + ((uintptr_t) a - 1)) & ~((uintptr_t) a - 1))

const int YE_POOL_ALIGEMENT = 16;
using namespace std;

using  PoolSNode = struct PoolSNode {
    //when failed over fine,the pointer of curchunk refer to next pool node
    int failed;
    u_char* last;
    u_char* end;
    PoolSNode* next;
    bitset<512> used;
    //the zone of data
    u_char* data;
};
//over 4k
using PoolLNode = struct PoolLNode {
    u_char* end;
    u_char* next;
    //the zone of data
    u_char* data;
};

using PoolHead = struct PoolHead {
    PoolSNode* next_s;
    //point to small chunk
    PoolSNode* current_s;
    //point to large chunk
    PoolLNode* next_l;
    PoolLNode* current_l;
};



//the pool of memory inorder to increase of efficiency which allocate the memory.
class MemPool {
public:
    MemPool():
    m_cache_line_size(cacheLineSize())
    {
    }

    ~MemPool() {

    }

    void createPool(int size);
    //alloc the mem
    u_char* allocateMem(int size);

    u_char* reallocMem(u_char* ptr,int size);
    //free the mem
    int freeMem(u_char* ptr);

    size_t align(size_t value) {
        auto cache_line = this->m_cache_line_size;
        return (value + (cache_line - 1)) & ~(cache_line - 1);
    }

    u_char* alignPtr(u_char* ptr) {
        auto cache_line = this->m_cache_line_size;
        return (u_char*)(((uintptr_t)(ptr) + (uintptr_t)(cache_line - 1)) & ~((uintptr_t)(cache_line - 1)));
    }
private:
    void initFreeList();
    //alloc 32k small chunk
    void allocSmChunk(int size);

    u_char* allocMemChunk(int size);
    //alloc


    void setBit(u_char* ptr,PoolSNode* chunk,bool is_used) {
        //set bit 0
        auto bitidx = this->bitIndex(ptr,chunk);
        chunk->used.set(bitidx, is_used);
    }

    bool getBit(PoolSNode* chunk,int index) {
        return chunk->used.test(index);
    }

    int bitIndex(u_char* ptr,PoolSNode* chunk) {
        return (ptr - chunk->data) / (this->m_cache_line_size / 8);
    }

    int freeLIndex(int sizeB) {
        return (sizeB * 8 / this->m_cache_line_size) - 1;
    }

    int offset(u_char* ptr,u_char* ptr1) {
        return (ptr1 - ptr);
    }

    int cLineBytes() {
        return this->m_cache_line_size / 8;
    }

    PoolSNode* findChunk(u_char* ptr);
    std::size_t getMemSize(u_char* ptr,PoolSNode* chunk);
private:
    PoolHead* m_head = nullptr;
    //[8,16,24,32,40,48,56,64,72,80,88,96]
    array<list<u_char*>,512> m_free_arr;
    int m_cache_line_size;
    int m_chunk_size;
};

#endif //ROBOT_MEMPOOL_H

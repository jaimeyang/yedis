//
// Created by jaime on 2021/2/26.
//

#include "MemPool.h"
#include <iostream>

void MemPool::createPool(int size) {
    void* p = (void*)this->m_head;
    auto err = posix_memalign(&p,YE_POOL_ALIGEMENT,size + sizeof(this->m_head));
    if (err != 0) {
        std::cout<<"posix memalign err "<<err<<std::endl;
        return;
    }
    this->m_head = (PoolHead*)p;
    this->m_head->current_s.failed = 0;
    this->m_head->current_s.next = nullptr;
    this->m_head->current_s.last = (u_char*)(this->m_head + sizeof(PoolSNode));
    this->m_head->current_s.end = (u_char*)(this->m_head + size + sizeof(this->m_head));
    this->m_head->current_l.next = nullptr;
    this->m_head->current_l.end = nullptr;
    this->initFreeList();
    return;
}

void MemPool::initFreeList() {
    //small mem [8,16,32,64,128,512,1024,2048,4096]B
    for (int i = 0; i < 9; ++i) {
        auto item = new list<u_char*>();
        this->m_free_arr[i] = (u_char*)item;
    }
}

void *MemPool::allocateMem(int size) {

    return nullptr;
}



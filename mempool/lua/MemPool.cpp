//
// Created by jaime on 2021/3/8.
//

#include "MemPool.h"
#include <iostream>

void MemPool::createPool(int size) {
    //alloc the head of pool
    this->m_head = new PoolHead();
    //alloc 32k at the beginning
    this->m_chunk_size = size;
    this->allocSmChunk(size);
    this->initFreeList();
    return;
}

void MemPool::initFreeList() {
    //small mem [8,16,32,64,128,512,1024,2048,4096]B
    for (int i = 0; i < 512; ++i) {
       auto item = list<u_char*>();
       this->m_free_arr[i] = item;
    }

}


void MemPool::allocSmChunk(int size) {
    for (auto i = 0; i < 8; i++) {
        void* p = nullptr;
        auto err = posix_memalign(&p,YE_POOL_ALIGEMENT,size);
        if (err != 0) {
            std::cout<<"posix memalign err "<<err<<std::endl;
            return;
        }
        auto node = (PoolSNode*)p;
        node->failed = 0;
        node->last = (u_char*)(p) + sizeof(PoolSNode);
        node->end = (u_char*)(p)+ size;
        node->next = this->m_head->next_s == nullptr ? nullptr : this->m_head->next_s;
        node->used.reset();
        node->data = node->last;
        this->m_head->next_s = node;
        this->m_head->current_s = node;
    }
}


u_char* MemPool::allocMemChunk(int size) {
    auto result = this->m_head->current_s->last;
    if (this->m_head->current_s->end - this->m_head->current_s->last <= size) {
        this->m_head->current_s = this->m_head->current_s->next;
        if (this->m_head->current_s == nullptr) {
            this->allocSmChunk(this->m_chunk_size);
        }
        result = this->m_head->current_s->last;
        this->m_head->current_s->last += size;
        return result;
    }
    this->m_head->current_s->last += size;
    return result;
}

//the logic of allocate mem from the mem pool
u_char* MemPool::allocateMem(int size) {
    if (size <= 0) {
        return nullptr;
    }
    //the size of bit
    auto sizeb = size * 8;
    sizeb = this->align(sizeb);
    //the size of bytes
    auto sizeB = sizeb / 8;
    auto fridx = this->freeLIndex(sizeB);
    //get the mem from the freelist
    if (this->m_free_arr[fridx].size() > 0) {
        auto ptr = this->m_free_arr[fridx].front();
        this->m_free_arr[fridx].pop_front();
        return ptr;
    }

    //get the mem from the chunk
    auto result = this->allocMemChunk(sizeB);
    this->setBit(result,this->m_head->current_s, true);
    return result;
}

u_char* MemPool::reallocMem(u_char *ptr, int size) {
    auto chunk = this->findChunk(ptr);
    auto a_size = this->getMemSize(ptr,chunk);
    if (a_size >= size) {
        return ptr;
    }
    size *= 2;
    auto sizeb = size * 8;
    sizeb = this->align(sizeb);
    auto sizeB = sizeb / 8;
    auto fridx = this->freeLIndex(sizeB);
    //todo
    if (fridx > 512) {

    }
    u_char* ret_ptr = nullptr;
    if (this->m_free_arr[fridx].size() > 0) {
        ret_ptr = this->m_free_arr[fridx].front();
        this->m_free_arr[fridx].pop_front();
    } else {
        ret_ptr = this->allocateMem(sizeB);
        this->setBit(ret_ptr,this->m_head->current_s, true);
    }
    memcpy(ret_ptr,ptr,a_size);
    return ret_ptr;
}

//to release the mem
int MemPool::freeMem(u_char* ptr) {
    if (ptr == nullptr) {
        return 0;
    }
    auto chunk = this->findChunk(ptr);
    auto size = this->getMemSize(ptr, chunk);
    auto frlidx = this->freeLIndex(size);
    this->m_free_arr[frlidx].push_back(ptr);

    return size;
}

PoolSNode* MemPool::findChunk(u_char* ptr) {
    auto p = this->m_head->next_s;
    while (p != nullptr) {
        auto temp = (u_char*)p;
        if ((ptr >= temp) && (ptr - temp < 4096)) {
            return p;
        }
        p = p->next;
    }
    return nullptr;
}
//return bytes
std::size_t MemPool::getMemSize(u_char* ptr,PoolSNode* chunk) {
    auto index = this->bitIndex(ptr,chunk);
    u_char* p = ptr;
    auto gap = 0;
    while (p != chunk->last) {
        p += this->cLineBytes();
        gap++;
        if (this->getBit(chunk,++index)) {
            break;
        }
    }
    return gap * this->cLineBytes();
}






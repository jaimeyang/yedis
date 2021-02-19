//
// Created by jaime on 2021/2/5.
//

#ifndef YEDIS_BUFFER_H
#define YEDIS_BUFFER_H

#include "Object.h"

const int MAX_SIZE = 1024;

class Buffer : public Object {
public:
    Buffer(){

    }
    ~Buffer(){

    }

public:
//    void write2buf()

private:
    int m_cout;
    int m_size;
};


#endif //YEDIS_BUFFER_H

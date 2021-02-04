//
// Created by jaime on 2021/2/4.
//

#ifndef YEDIS_INTERGER_H
#define YEDIS_INTERGER_H

#include "Object.h"

class Interger : public Object {
public:
    Interger(int data)
    : m_data(data){

    }
    ~Interger(){

    }

public:
    int get(){
        return m_data;
    }

private:
    int m_data;
};


#endif //YEDIS_INTERGER_H

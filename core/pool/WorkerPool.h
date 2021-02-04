//
// Created by jaime on 2021/2/3.
//

#ifndef YEDIS_WORKERPOOL_H
#define YEDIS_WORKERPOOL_H

#include <array>
#include <memory>

using namespace std;

const int  MAX_WORKER = 1;


class WorkerPool {
private:
    WorkerPool(){

    }
    ~WorkerPool(){

    }

private:
    unique_ptr<array<int,2>> createSocketPair();


public:
    static WorkerPool* getInsance(){
        if ( m_instance == nullptr ){
            m_instance = new WorkerPool();
        };
        return m_instance;
    }

    void createWorker();
    void notiyEventAdd(int newfd);
private:
    static WorkerPool* m_instance;
    array<int,MAX_WORKER> m_sps;
};


#endif //YEDIS_WORKERPOOL_H

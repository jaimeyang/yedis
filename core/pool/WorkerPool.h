//
// Created by jaime on 2021/2/3.
//工作线程池
//todo 没有完成，后续添加支持

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
    //为什么是2，因为socketpair会返回两个文件描述符
    unique_ptr<array<int,2>> createSocketPair();
public:
    static WorkerPool* getInsance(){
        if ( m_instance == nullptr ){
            m_instance = new WorkerPool();
        };
        return m_instance;
    }

    void createWorker();
    //告诉子线程已经有新连接了
    void notiyEventAdd(int newfd);
private:
    static WorkerPool* m_instance;
    //保存socketpair，MAX_WORKER后续通过配置文件实现
    array<int,MAX_WORKER> m_sps;
};


#endif //YEDIS_WORKERPOOL_H

//
// Created by jaime on 2021/2/4.
//读写事件回调

#ifndef YEDIS_WORKEROBJECT_H
#define YEDIS_WORKEROBJECT_H

#include "TcpEventObj.h"
#include "EpollDispatcher.h"
#include "Redis.h"

class WorkerObject : public TcpEventObj {
public:
    WorkerObject(shared_ptr<Distpacher> dispatcher):
    m_dispatcher(dispatcher){
        m_redis = std::make_unique<Redis>();
        auto addr = std::make_unique<string_view>("192.168.1.132");
        m_redis->connect(std::move(addr),6379);
    }
    ~WorkerObject(){

    }
public:
    void exceptEventCb(int fd, unique_ptr<Object> obj) override;
    void readEventCb(int fd, unique_ptr<Object> obj) override;
    void writeEventCb(int fd, unique_ptr<Object> obj) override;

private:
    shared_ptr<Distpacher> m_dispatcher;
    //todo 后面实现redis的连接池
    unique_ptr<Redis> m_redis;
};


#endif //YEDIS_WORKEROBJECT_H

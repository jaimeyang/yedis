//
// Created by jaime on 2021/2/4.
//

#ifndef YEDIS_WORKEROBJECT_H
#define YEDIS_WORKEROBJECT_H

#include "TcpEventObj.h"
#include "EpollDispatcher.h"

class WorkerObject : public TcpEventObj {
public:
    WorkerObject(shared_ptr<Distpacher> dispatcher):
    m_dispatcher(dispatcher){

    }
    ~WorkerObject(){

    }
public:
    void exceptEventCb(int fd, unique_ptr<Object> obj) override;
    void readEventCb(int fd, unique_ptr<Object> obj) override;
    void writeEventCb(int fd, unique_ptr<Object> obj) override;

private:
    shared_ptr<Distpacher> m_dispatcher;
};


#endif //YEDIS_WORKEROBJECT_H

//
// Created by jaime on 2021/1/30.
//

#include "Worker.h"
#include "WorkerObject.h"
#include "EventFactory.h"
#include "Interger.h"

//子线程主循环
void Worker::run() {
    this->m_distpacher = std::make_shared<EpollDispatcher>();
    this->m_distpacher->initDispatch();
    auto obj = std::make_unique<WorkerObject>(this->m_distpacher);
    //添加socketpair的读事件
    auto data = make_unique<Interger>(this->m_fd);
    auto event = EventFactory::create()->createEvent(EventType::READ_EVENT,this->m_fd,std::move(obj), std::move(data));
    this->m_distpacher->addEvent(std::move(event));
    while ( true ) {
        this->m_distpacher->disPatch();
    }
}

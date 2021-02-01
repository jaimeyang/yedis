//
// Created by jaime on 2021/1/29.
//

#ifndef ROBOT_EPOLLDISPATCHER_H
#define ROBOT_EPOLLDISPATCHER_H

#include "Distpacher.h"

class EpollDispatcher : public Distpacher {
public:
    void initDispatch() override;
    void disPatch() override;
    void addEvent(unique_ptr<Event> event) override;

private:
    int m_epoll_fd;
    struct epoll_event* events;
    unordered_map<int,unique_ptr<Event>> m_event_map;
};


#endif //ROBOT_EPOLLDISPATCHER_H

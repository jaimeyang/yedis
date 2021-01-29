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
};


#endif //ROBOT_EPOLLDISPATCHER_H

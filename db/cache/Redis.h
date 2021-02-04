//
// Created by jaime on 2021/2/2.
//

#ifndef ROBOT_REDIS_H
#define ROBOT_REDIS_H

#include <hiredis/hiredis.h>
#include <string_view>
#include <memory>
#include <vector>


using namespace std;

class Redis {
public:
    Redis(){

    }
    ~Redis(){
        redisFree(this->m_context);
    }

public:
    void connect(unique_ptr<std::string_view> addr,int port);
    unique_ptr<string> execCommand(const string_view& command);
public:
    redisContext* m_context = nullptr;
};


#endif //ROBOT_REDIS_H

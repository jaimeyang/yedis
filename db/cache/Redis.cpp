//
// Created by jaime on 2021/2/2.
//

#include <iostream>
#include "Redis.h"

void Redis::connect(unique_ptr<std::string_view> addr,int port){
    this->m_context = redisConnect(addr->data(),port);
    if( this->m_context == nullptr ){
        std::cout<<"connect redis error "<<this->m_context->errstr<<std::endl;
        return;
    }
}

void Redis::execCommand(unique_ptr<string_view> command){
    auto reply = (redisReply*)redisCommand(this->m_context,command->data());
    if ( reply != nullptr ) {
        std::cout<<"reply str is "<<reply->str<<std::endl;
        freeReplyObject(reply);
    }
    std::cout<<"execcommand reply is empty"<<std::endl;
}

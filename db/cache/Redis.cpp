//
// Created by jaime on 2021/2/2.
//

#include <iostream>
#include <cstring>
#include "Redis.h"

void Redis::connect(string_view& addr,int port){
    this->m_context = redisConnect(addr.data(),port);
    if( this->m_context == nullptr ){
        std::cout<<"connect redis error "<<this->m_context->errstr<<std::endl;
        return;
    }
    std::cout<<"connect scuess"<<std::endl;
}



unique_ptr<string> Redis::execCommand(const string_view& command){
    auto reply = (redisReply*)redisCommand(this->m_context,command.data());
    if ( reply->elements > 0 ) {
        auto ret = make_unique<string>("");
        for (int i = 0; i < reply->elements; ++i) {
            auto ele = reply->element[i];
            if ( ele->str != nullptr ){
                ret->append(ele->str);
                ret->append("\n");
            }
        }
        freeReplyObject(reply);
        return std::move(ret);
    }
    if ( reply->str != nullptr ){
        printf("resp is %s\n",reply->str);
        auto result = make_unique<string>(reply->str);
        freeReplyObject(reply);
        return std::move(result);
    }
    return nullptr;
}

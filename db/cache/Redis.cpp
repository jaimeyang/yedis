//
// Created by jaime on 2021/2/2.
//

#include <iostream>
#include <cstring>
#include "Redis.h"

void Redis::connect(unique_ptr<std::string_view> addr,int port){
    this->m_context = redisConnect(addr->data(),port);
    if( this->m_context == nullptr ){
        std::cout<<"connect redis error "<<this->m_context->errstr<<std::endl;
        return;
    }
    std::cout<<"connect scuess"<<std::endl;
}
//todo 为什么不能用string_view
unique_ptr<string> Redis::execCommand(const string_view& command){
    auto reply = (redisReply*)redisCommand(this->m_context,command.data());
    if ( reply->elements > 0 ) {
        printf("replay str is %s\n",reply->str);
        auto ret = make_unique<string>("");
        for (int i = 0; i < reply->elements; ++i) {
            auto ele = reply->element[i];
            auto test = string(ele->str);
            ret->append(ele->str);
            ret->append("\n");
        }
        freeReplyObject(reply);
        return std::move(ret);
    }
    return nullptr;
}

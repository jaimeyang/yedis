//
// Created by jaime on 2021/2/2.
//

#ifndef _REDIS_H
#define _REDIS_H

#ifdef __cplusplus
extern "C" {
    #include <hiredis/hiredis.h>
}
#endif
#include <string>
#include <memory>
#include <vector>

using namespace std;

namespace yedis {
    class Redis {
        public:
            Redis() {
            
            }
            ~Redis() {
                redisFree(this->m_context);
            }               

        public:
            bool connect(const string_view& addr, int port);
            unique_ptr<string> execCommand(const string_view &command);
        public:
            redisContext *m_context = nullptr;
    };

}

#endif //ROBOT_REDIS_H

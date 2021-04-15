#ifndef _MYSQL_H_
#define _MYSQL_H_

#include <string>
#include "mysqlx/xdevapi.h"
#include "LuaFactory.h"
#include <vector>
#include <iostream>
#include <unistd.h>


using namespace std;
using namespace mysqlx;
//todo C++ conenctor不支持异步，考虑到并发性，每一个SQL实例应该放到一个线程池里面
namespace yedis {
    class Mysql final
    {    
    public:
        Mysql() = default;
        //复制构造函数
        Mysql(const Mysql& mysql) = delete;
        //移动构造函数
        Mysql(const Mysql&& mysql) = delete;
        //复制赋值运算符
        Mysql& operator=(const Mysql& mysql) = delete;
        //移动赋值运算符
        Mysql& operator=(const Mysql&& mysql) = delete;
        ~Mysql() {
            this->close();
        };
    public:
        //username:pwd@addr/dbname
        void open(const std::string& url);
        void close();

    
        void insert(const std::string& schema,const std::string& tb,const luabridge::LuaRef& ref);
        void update(const std::string& schema,const std::string& tb,const luabridge::LuaRef& ref);
    private:
        Client* m_client;
        Session* m_session;
    };

}




#endif
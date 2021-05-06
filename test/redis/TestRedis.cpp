
#include "TestRedis.h"
#include "Redis.h"
#include <memory>
#include <string_view>
#include <iostream>
#include <thread>

using namespace std;
using namespace yedis;


class RedisWorker {
    public:
        void operator()() const {
             Redis r;
            const string_view addr("192.168.1.179");
            auto port = 6379;
            auto ret = r.connect(addr,port);

            if (ret) {

                auto result = r.execCommand("RPUSH mylist \"Hello\"");
                cout<<"result "<<result.get()<<endl;
            }
            // while (ret) {
            //     sleep(1);
            // }
            
        }
};

TEST_F(TestRedis,test_connect) {
   thread t{RedisWorker()};
   
   t.join();
}
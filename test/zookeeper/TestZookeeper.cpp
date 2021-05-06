//
// Created by jaime on 2021/3/18.
//

#include "TestZookeeper.h"
#include <thread>
#include <iostream>

using namespace std;
#ifdef __cplusplus
extern "C" {


static void data_completion(int rc, const char *value, int value_len,const struct Stat *stat, const void *data) {
    cout<<"data_completion rc--"<<rc<<endl;
    // cout<<"data_completion value--"<<value<<endl;
    // cout<<"data_completion value_len--"<<value_len<<endl;
};


static void strings_completion(int rc,const struct String_vector *strings, const void *data) {
    cout<<"strings_completion_t rc--"<<rc<<endl;
    // if (strings != nullptr && strings->data != NULL) {
    //     cout<<"strings_completion_t value--"<<*strings->data<<endl;
    // }
    // cout<<"value_len--"<<value_len<<endl;
}


static void watcher(zhandle_t *zkH, int type, int state, const char *path, void *watcherCtx)
{
    cout<<"type "<<type<<endl;
    cout<<"state "<<state<<endl;
    cout<<"path "<<path<<endl;
    if (type == ZOO_SESSION_EVENT) {
        if (state == ZOO_CONNECTED_STATE) {
        #if 0
            int rc = zoo_awget(zkH,"/data",watcher,nullptr,data_completion,nullptr);
            if (rc != ZOK) {
                cout<<"rc is "<<endl;
            }
        #endif
        #if 1
            int rc = zoo_awget_children(zkH,"/data/data1",watcher,nullptr,strings_completion,nullptr);
            if (rc != ZOK) {
                cout<<"ZOO_CONNECTED_STATE faile "<<rc<<endl;
            }
        #endif
        } else if (state == ZOO_NOTCONNECTED_STATE ) {

        } else if (state == ZOO_EXPIRED_SESSION_STATE) {
            // zookeeper_close(zkH);
        }
    } else if (type == ZOO_CREATED_EVENT) {

    } else if (type == ZOO_DELETED_EVENT) {

    } else if (type == ZOO_CHANGED_EVENT) {
       int rc = zoo_awget_children(zkH,"/data/data1",watcher,nullptr,strings_completion,nullptr);
       if (rc != ZOK) {
           cout<<"ZOO_CHANGED_EVENT faile "<<rc<<endl;
       }
        
    } else if (type == ZOO_CHILD_EVENT) {

    } else if (type == ZOO_NOTWATCHING_EVENT) {

    }

}

};
#endif

class TestZkClientWatch {
public:
    TestZkClientWatch() = default;
    void operator()() const {
        zoo_set_debug_level(ZOO_LOG_LEVEL_ERROR);
        // zookeeper_init returns the handler upon a successful connection, null otherwise
        auto zkHandler = zookeeper_init("192.168.1.146:2181", watcher, 10000, 0, 0, 0);
        if (!zkHandler) {
             printf("Connection establish fail with Zookeeper. \n");
        } else {
            printf("Connection established with Zookeeper. \n");
        }
        auto i = 0;
        while (1){
            if (i == 6) {
                auto rs = zoo_acreate(zkHandler,"/data/data1", "", 0, &ZOO_CREATOR_ALL_ACL,ZOO_PERSISTENT,nullptr,nullptr);
                if (rs != ZOK) {
                    cout<<"zoo_acreate fail"<<rs<<endl;
                    return;
                }
                cout<<"create scuess"<<endl;
            }
            sleep(1);
            i++;
        }
        
        
        // // Close Zookeeper connection
        // zookeeper_close(zkHandler);
      
    }
    
};

class TestZkClient {
public:
    TestZkClient() = default;
    void operator()() const {
        
    }
};




TEST_F(TestZookeeper,test_conect) {
   
    thread t1{TestZkClientWatch()};

    t1.join();
}
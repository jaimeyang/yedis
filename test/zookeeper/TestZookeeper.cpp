//
// Created by jaime on 2021/3/18.
//

#include "TestZookeeper.h"

#ifdef __cplusplus
extern "C" {
static void watcher(zhandle_t *zkH, int type, int state, const char *path, void *watcherCtx)
{
    if (type == ZOO_SESSION_EVENT) {

        // state refers to states of zookeeper connection.
        // To keep it simple, we would demonstrate these 3: ZOO_EXPIRED_SESSION_STATE, ZOO_CONNECTED_STATE, ZOO_NOTCONNECTED_STATE
        // If you are using ACL, you should be aware of an authentication failure state - ZOO_AUTH_FAILED_STATE
        if (state == ZOO_CONNECTED_STATE) {
        } else if (state == ZOO_NOTCONNECTED_STATE ) {
        } else if (state == ZOO_EXPIRED_SESSION_STATE) {
            zookeeper_close(zkH);
        }
    }
}

};
#endif


TEST_F(TestZookeeper,test_conect) {
    zoo_set_debug_level(ZOO_LOG_LEVEL_DEBUG);

    // zookeeper_init returns the handler upon a successful connection, null otherwise
    auto zkHandler = zookeeper_init("192.168.1.146:2181", watcher, 10000, 0, 0, 0);

    if (!zkHandler) {

    }else{
        printf("Connection established with Zookeeper. \n");
    }

    // Close Zookeeper connection
    zookeeper_close(zkHandler);
}
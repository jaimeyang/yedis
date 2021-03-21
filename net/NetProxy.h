//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_NETPROXY_H
#define YEDIS_NETPROXY_H

#include "IMultiIo.h"
#include <memory>

#ifdef LINUX
#include "LinuxListen.h"
#include "LinuxConnect.h"
#endif

#ifdef EPOLL
#include "Epoll.h"
#endif



using namespace std;

namespace yedis {
    //网络代理类，屏蔽掉不同平台的网络实现
    class NetProxy {
    public:
        NetProxy()
        {
#ifdef LINUX
            m_server = make_unique<LinuxListen>();
#endif
#ifdef EPOLL
            m_io = make_unique<Epoll>();
#endif
        }
        void initNet();
        void addFd(int fd);
        void rmFd(int fd);
        void regEvent(INetEvent* event);
        void startServer(const string& addr);
        void connect(const string& addr);
    private:
        unique_ptr<IMultiIo> m_io;
        unique_ptr<StreamListen> m_server;
        unique_ptr<StreamConnect> m_connect;
    };

}


#endif //YEDIS_NETPROXY_H

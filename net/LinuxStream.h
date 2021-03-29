//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_LINUXSTREAM_H
#define YEDIS_LINUXSTREAM_H
#include "IStream.h"
#include "Wmanager.h"
#include "StreamBuf.h"
#include <unordered_map>

using namespace std;

namespace yedis {
    class LinuxStream : public INetEvent {
    public:
        LinuxStream() :
        m_wm(make_unique<Wmanager>())
        {
            m_wm->createPool(2);
        }
        ~LinuxStream() {

        }
        void inEvent(int fd) override;
        void outEvent(int fd) override;
        void timeOutEvent(int fd) override;
        void errEvent(int fd) override;

    private:
        unique_ptr<Wmanager> m_wm;
        unordered_map<int,unique_ptr<StreamBuf>> m_bufs;
    };
}




#endif //YEDIS_LINUXSTREAM_H

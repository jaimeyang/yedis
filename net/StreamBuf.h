//
// Created by jaime on 2021/3/27.
//

#ifndef YEDIS_STREAMBUF_H
#define YEDIS_STREAMBUF_H

#include <vector>
#include <iostream>

using namespace std;

namespace yedis {
    class StreamBuf {
    public:
        StreamBuf() {
            this->setSize(1024);
        }
        void setSize(int size) {
            this->m_data.reserve(size);
        }
        //data :返回可以读的位置
        //返回值是读取的字节数
        int read(char** data,int n);
        //成功处理的字节数
        void readFinish(int n);
        int readAble() {
            return (this->m_w_index - this->m_r_index) % this->m_data.capacity();
        }
        int writeAable() {
            return (this->m_r_index - this->m_w_index - 1) % this->m_data.capacity();
        }
        //返回开始写的位置
        char* write(){
            return this->m_data.data() + this->m_w_index;
        }
        //成功写入的字节数
        void writeFinish(int n);
    private:
        //保存二进制
        vector<char> m_data;
        //the position of read
        int m_r_index = 0;
        //the position of write
        int m_w_index = 0;
    };
}


#endif //YEDIS_STREAMBUF_H

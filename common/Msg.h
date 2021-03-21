//
// Created by jaime on 2021/3/20.
//

#ifndef YEDIS_MSG_H
#define YEDIS_MSG_H
#include <vector>

using namespace std;

namespace yedis {
    class Msg {
    public:
        unsigned char id = 0;
        vector<char> data;
    };
}


#endif //YEDIS_MSG_H

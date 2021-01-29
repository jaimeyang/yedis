//
// Created by jaime on 2021/1/28.
//

#ifndef ROBOT_SERVER_H
#define ROBOT_SERVER_H


class Server {
public:
    Server(){

    }
    ~Server(){

    }
    void listenServer();
    //主循环
    void runServer();
    void acceptServer();
public:
    int m_lifd;
};


#endif //ROBOT_SERVER_H

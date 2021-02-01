//
// Created by jaime on 2021/1/29.
//对象基类，里面的对象都继承这个类进行扩展

#ifndef ROBOT_OBJECT_H
#define ROBOT_OBJECT_H

#include <string_view>
#include <memory>

using namespace std;
//todo 考虑使用模板类
class Object {
public:
    Object() {

    }

    ~Object(){

    }
    virtual void readEventCb(int fd,unique_ptr<Object> obj) = 0;
    virtual void writeEventCb(int fd,unique_ptr<Object> obj) = 0;
    virtual void exceptEventCb(int fd,unique_ptr<Object> obj) = 0;
private:

};


#endif //ROBOT_OBJECT_H

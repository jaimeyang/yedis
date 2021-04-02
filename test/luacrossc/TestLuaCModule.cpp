

#ifndef YEDIS_TESTLUACMODULE_H
#define YEDIS_TESTLUACMODULE_H

#include "gtest/gtest.h"
#include <memory>
#include <iostream>



#ifdef __cplusplus
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif



#include "LuaBridge/LuaBridge.h"

using namespace std;

const char* lua_path = "script/test/luamodule/TestLuaCModule.lua";



class TestLuaCModule : public ::testing::Test {
public:
    void SetUp() {
       
    }

    void TestBody() {

    }

    void TearDown() {

    }
private:
    
};

class TestModule {
    public:
    //gc 的时候会自动调用析构函数
        ~TestModule() {
            cout<<"~~~~"<<endl;
        }
    public:
        int test(int a,int b) {
            return a + b;
            // cout<<"test"<<endl;
        }

        void gc() {
            cout<<"gc"<<endl;
        }
};




TEST_F(TestLuaCModule,test_reg_func) {

    lua_State* L = luaL_newstate();
    luaL_openlibs(L);

    luabridge::getGlobalNamespace(L)
        .beginClass<TestModule>("TestModule")
        .addConstructor<void(*)()>()
        .addFunction("test",&TestModule::test)
        .endClass();
    int ret = luaL_dofile(L, lua_path);
    if ( ret ) {
        fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(L, -1));
    }
}

#endif
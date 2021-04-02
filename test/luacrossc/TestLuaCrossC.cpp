//
// Created by jaime on 2021/2/22.
//

#ifndef YEDIS_TESTLUACROSSC_H
#define YEDIS_TESTLUACROSSC_H

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

#include "gtest/gtest.h"
#include <iostream>

using namespace std;

const char* m_scr_name = "../script/test/luacrossc/TestLuaCrossC.lua";

int performWithDelay(lua_State* l) {
    lua_pushvalue(l,-2);
    auto handler = luaL_ref(l,LUA_REGISTRYINDEX);
    lua_pushvalue(l,-1);
    lua_rawgeti(l,LUA_REGISTRYINDEX,handler);
    auto ret = lua_pcall(l,0,0,0);
    if (ret != 0) {
        cout<<"perform with  delay "<<ret<<endl;
        return 0;
    }
    luaL_unref(l,LUA_REGISTRYINDEX,handler);
    lua_pop(l,-1);
    return 0;
}


class TestLuaCrossC : public ::testing::Test {
public:
    void SetUp() {
        this->m_l = luaL_newstate();
        luaL_openlibs(this->m_l);
        /* 运行脚本 */
        int ret = luaL_dofile(this->m_l, m_scr_name);
        if ( ret ) {
            fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(this->m_l, -1));
        }
        lua_pcall(this->m_l,0,0,0);
        lua_register(this->m_l,"performwithdelay",performWithDelay);
    }

    void TestBody() {

    }

    void TearDown() {

    }



    auto get_lua() {
        return this->m_l;
    }

private:
    lua_State* m_l = nullptr;
};

TEST_F(TestLuaCrossC,test_lua_main) {
    lua_pcall(this->get_lua(),0,0,0);
    lua_getglobal(this->get_lua(),"main");
    auto s = lua_pcall(this->get_lua(),0,1,0);
    if ( s != LUA_OK ) {
        fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(this->get_lua(), -1));
    }
    size_t len = 40;
    char* v = const_cast<char *>(lua_tolstring(this->get_lua(), -1, &len));
    ASSERT_STREQ(v,"sqwertyuiopasdfghjklzxcvbnm1234567890123411");
}


TEST_F(TestLuaCrossC,test_timer_gc) {
    while (true) {
        lua_getglobal(this->get_lua(),"timer");
        auto s = lua_pcall(this->get_lua(),0,1,0);
        if ( s != LUA_OK ) {
            fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(this->get_lua(), -1));
        }
        lua_pop(this->get_lua(),-1);
        sleep(1);
    }
}


TEST_F(TestLuaCrossC,test_pushcclosure) {
    
}

#endif //YEDIS_TESTLUACROSSC_H

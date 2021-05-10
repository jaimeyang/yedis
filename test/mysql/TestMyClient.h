

#ifndef _TEST_MYCLIENT_H_
#define _TEST_MYCLIENT_H_

#include "gtest/gtest.h"
#include "MySqlclient.h"
#include <memory>
#include <string>
#include "LuaFactory.h"

// using namespace yedis;

class TestMyClient : public testing::Test {

public:
    void SetUp() override {
        lua_State *l = nullptr;
        string path("script/test/mysql/TestUser.lua");
        yedis::LuaFactory::getFactory()->buildSlua(path, [&l](lua_State *L) {
            l = L;
        });

        yedis::LuaFactory::getFactory()->registerMysql(l);
        auto v = luabridge::getGlobal(l, "Test");
        v();
    }

    void TestBody() override
    {
    }

    void TearDown() override
    {
    }

public:
private:
};

#endif
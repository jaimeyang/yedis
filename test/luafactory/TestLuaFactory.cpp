
#include "TestLuaFactory.h"
#include "LuaFactory.h"
#include "LuaBridge/LuaBridge.h"


using namespace yedis;
const string& lua_path = "script/test/luafactory/TestLuaFactory.lua";

int add_result = 0;


class TestLua {
    public:
        TestLua() = default;
        ~TestLua() = default;

    public:

        int add(int a,int b) {
            add_result = a + b;
            return add_result;
        }

        int getc() {
            return this->c;
        }
    private:
        int c;
};

//todo document https://vinniefalco.github.io/LuaBridge/Manual.html#s4.1
// https://github.com/vinniefalco/LuaBridge
TEST_F(TestLuaFactory,test_lua_factory_buildslua) {
    lua_State* l = nullptr;
    LuaFactory::getFactory()->buildSlua(lua_path,[&l](lua_State* L) {
        auto test = luabridge::getGlobalNamespace(L).beginClass<TestLua>("TestLua")
            .addConstructor<void(*)()>()
            .addFunction("add",&TestLua::add)
            .endClass();

            l = L;
    });
    //call lua
    auto v = luabridge::getGlobal(l,"add");
    v(1,6);
    ASSERT_EQ(7,add_result);
    
}
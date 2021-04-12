
#include "LuaFactory.h"
#include "StreamBuf.h"
#include "LuaBridge/LuaBridge.h"

yedis::LuaFactory* yedis::LuaFactory::m_lc = nullptr;


void yedis::LuaFactory::buildSlua(const string& path,function<void(lua_State*)> lamba) {
    lua_State* L = luaL_newstate();
    luaL_openlibs(L);
    if (lamba != nullptr) {
        lamba(L);
    }
    
    int ret = luaL_dofile(L,path.c_str());
    if ( ret ) {
        fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(L, -1));
        return;
    }
    return;
}

void yedis::LuaFactory::buildStreamBuf() {
    string path("script/StreamBuf.lua");
    lua_State* L = nullptr;
    this->buildSlua(path,[&L](lua_State* l){
        luabridge::getGlobalNamespace(l).beginClass<StreamBuf>("StreamBuf")
        .addConstructor<void(*)()>()
        .addFunction("write",&StreamBuf::write)
        .endClass();
        L = l;
    });
    this->m_streambuf_l = L;
}

void yedis::LuaFactory::callStreamBufLua(string& funcname) {
    auto f = luabridge::getGlobal(this->m_streambuf_l,funcname.c_str());
    f();
}
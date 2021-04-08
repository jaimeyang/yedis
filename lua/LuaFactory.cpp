
#include "LuaFactory.h"

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
//
// Created by jaime on 2021/1/28.
//

#include "core/Server.h"


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

void loadLua() {
    auto l = luaL_newstate();
    luaL_openlibs(l);

    /* 运行脚本 */
    int ret = luaL_dofile(l, "../script/main.lua");
    if ( ret ) {
        fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(l, -1));
    }
    lua_pcall(l,0,0,0);
    lua_getglobal(l,"main");
    auto s = lua_pcall(l,0,1,0);
    if ( s != LUA_OK ) {
        fprintf(stderr, "\nFATAL ERROR:%s\n\n", lua_tostring(l, -1));
    }
    size_t len = 40;
    char* v = const_cast<char *>(lua_tolstring(l, -1, &len));
    printf("v is %s\n",v);

//    free((void *) v);
    lua_getglobal(l,"test");
    lua_pcall(l,0,1,0);
    lua_close(l);
    printf("v is %s\n",v);
    free((void *) v);
}

int main(int argc, char* argv[]){
//    Server* s = new Server;
//    s->runServer();
    loadLua();
}
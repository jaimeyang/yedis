//
// Created by jaime on 2021/2/19.
//

#ifndef YEDIS_LUACOMMON_H
#define YEDIS_LUACOMMON_H
//lua头文件
#ifdef __cplusplus
extern "C" {
#include "lua.h"
#include <lauxlib.h>
#include <lualib.h>
}
#else
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#endif

#include <memory>
#include <string>

using namespace std;
class LuaCommon{
public:
    LuaCommon(lua_State* l):
            m_lua(l){

    }
    ~LuaCommon(){

    }

public:
    void lua_len(int& len,int index){
        len = luaL_len(this->m_lua,index);
    }

    void lua_push(string& v){
        int len = v.length();
        lua_pushlstring(this->m_lua,v.c_str(),len);
    }

//    void lua_push(BinStr* data){
//        lua_pushlstring(this->m_lua,data->data.get(),data->len);
//    }

//    void lua_push(const char* v){
//        int len = strlen(v);
//        lua_pushlstring(this->m_lua,v,len);
//    }

    void lua_push(int v){
        lua_pushnumber(this->m_lua,v);
    }

    void lua_push(bool v){
        lua_pushboolean(this->m_lua,v);
    }

    void lua_get_table(int index){
        lua_gettable(m_lua,index);
    }

    void lua_to(unsigned int* v,int index){
        if ( lua_isnumber(m_lua,index) ) {
            *v = lua_tonumber(m_lua,index);
            return;
        }
        printf("lua_to must return a number.\n");
    }

    void lua_to(int* v,int index){
        if ( lua_isnumber(m_lua,index) ) {
            *v = lua_tonumber(m_lua,index);
            return;
        }
        printf("lua_to must return a number.\n");
    }

    void lua_to(string* v,int index){
        if ( lua_isstring(m_lua,index) ) {
            v->append(lua_tostring(m_lua,index));
            return;
        }
        printf("lua_to must return a string.\n");

    }

    void lua_to(string* v,int index,size_t len){
        if ( lua_isstring(m_lua,index) ) {
            v->append(lua_tolstring(m_lua,index,&len));
            return;
        }
        printf("lua_to must return a string.\n");

    }

//    unique_ptr<char> lua_to(int index,size_t len){
//        if ( lua_isstring(m_lua,index) ) {
//            char* v = lua_tolstring(m_lua,index,&len);
//            unique_ptr<char> result = make_unique<char>(len);
//            memcpy(result.get(),v,len);
//            return std::move(result);
//        }
//        printf("lua_to must return a string.\n");
//    }
    const char* lua_to(int index,std::size_t len) {
        const char* v = lua_tolstring(m_lua,index,&len);
        printf("data is %s\n",v);
        free((void *) v);
    }

    void lua_to(char* v,int index){
        if ( lua_isstring(m_lua,index) ) {
            const char* d = lua_tostring(m_lua,index);
            v = const_cast<char *>(d);
            return;
        }
        v = nullptr;
        printf("lua_to must return a string.\n");

    }

    void lua_to(bool* v,int index){
        if ( lua_isboolean(m_lua,index) ) {
            *v = lua_toboolean(m_lua,index);
            return;
        }
        printf("lua_to must return a boolean.\n");
    }

//    void lua_to(BinStr* binStr,int index){
//        lua_to(&(binStr->len),index);
//        binStr->data = lua_to(index+1,binStr->len);
//    }
private:
    lua_State* m_lua;
};
#endif //YEDIS_LUACOMMON_H

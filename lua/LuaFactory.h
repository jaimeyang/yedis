#ifndef _LUA_FACTORY_H_
#define _LUA_FACTORY_H_

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


#include <functional>
#include <string>

using namespace std;

namespace yedis {
    class LuaFactory {
        private:
            LuaFactory() = default;
        public:
            static LuaFactory* getFactory() {
                if (m_lc != nullptr) {
                    m_lc = new LuaFactory();
                }

                return m_lc;
            }
            void buildSlua(const string& path,function<void(lua_State*)> lamba = nullptr);
        private:
            static LuaFactory* m_lc;
    };
}



#endif
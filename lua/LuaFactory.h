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

using namespace std;

namespace yedis {
    class LuaFctory {
        private:
            LuaFctory() = default;
        public:
            static LuaFctory* getFactory() {
                if (m_lc != nullptr) {
                    m_lc = new LuaFctory();
                }

                return m_lc;
            }
            void buildSlua(string& path,function<void(lua_State)> lamba);
        private:
            static LuaFctory* m_lc;
    };
}



#endif
#ifndef _LUA_FACTORY_H_
#define _LUA_FACTORY_H_

#include <functional>

using namespace std;

namespace yedis {
    class LuaFctory {
        private:
            LuaFctory() = default;
        public:
            static LuaFctory* getFactory() {
                if (m_lc ) {
                    m_lc = new LuaFctory();
                }

                return m_lc;
            }
            void buildSlua(string& path,)
        private:
            static LuaFctory* m_lc;
    };
}



#endif
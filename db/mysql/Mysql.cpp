
#include "Mysql.h"

void yedis::Mysql::open(const std::string &url) {
    this->m_client = new Client(url.c_str());

    this->m_session = new Session(*this->m_client);
}

void yedis::Mysql::close() {
    this->m_client->close();
    this->m_session->close();

    delete this->m_client;
    this->m_client = nullptr;
    this->m_session = nullptr;
}

void yedis::Mysql::insert(const std::string &schema, const std::string &tb, const luabridge::LuaRef &ref) {
    auto table = this->m_session->getSchema(schema).getTable(tb);
    auto l = ref.state();
    ref.push(l);
    luabridge::push(l, luabridge::Nil());
    Row r;
    while (lua_next(l, -2)) {
        luabridge::LuaRef key = luabridge::LuaRef::fromStack(l, -2);
        if (!key.isNumber()) {
            cout << "key must number " << key << endl;
            return;
        }

        luabridge::LuaRef val = luabridge::LuaRef::fromStack(l, -1);
        unsigned long pos = key.cast<unsigned long>();
        if (val.isBool()) {
            Value v(val.cast<bool>());
            r.set(pos - 1, v);
        } else if (val.isNumber()) {
            Value v(val.cast<float>());
            r.set(pos - 1, v);
        }
        else {
            Value v(val.cast<std::string>());
            r.set(pos - 1, v);
        }
        lua_pop(l, 1);
    }
    table.insert().values(r).execute();
}


void yedis::Mysql::update(const std::string& schema,const std::string& tb,const luabridge::LuaRef& ref) {
    auto table = this->m_session->getSchema(schema).getTable(tb);
    table.update().set().where().orderBy().limit().execute()
}

#include "TestMysql.h"
#include "LuaFactory.h"
#include "mysqlx/xdevapi.h"
#include <string>
#include "LuaBridge/LuaBridge.h"
#include <iostream>
#include "Mysql.h"

using namespace std;

using namespace mysqlx;

using namespace yedis;

const std::string& mysql_lua = "script/test/mysql/TestMysql.lua";


TEST_F(TestMysql,test_connector) {
    Session sess("192.168.1.113", 33060, "yedis", "123456");
    Schema db= sess.getSchema("yedis");
    // // or Schema db(sess, "test");

    auto tb = db.getTable("user");
    // Collection myColl = db.getCollections("user");
    // // or Collection myColl(db, "my_collection");

    auto myDocs = tb.select("user_name").where("id = 1").execute();                          
}

TEST_F(TestMysql,test_connect_single) {
    std::string usr("yedis");
    std::string pwd("123456");

    // Connect to MySQL Server on a network machine
    Session mySession(SessionOption::HOST, "192.168.1.113",
                  SessionOption::PORT, 33060,
                  SessionOption::USER, usr,
                  SessionOption::PWD, pwd);

    // An alternative way of defining session settings.

    // SessionSettings settings(SessionOption::HOST,"localhost",
    //                      SessionOption::PORT, 33060);

    // settings.set(SessionOption::USER, usr);
    // settings.set(SessionOption::PWD, pwd);

    // Session mySession(settings);


    Schema db = mySession.getSchema("yedis");
    
    auto tb = db.getTable("user");
    auto myDocs = tb.select("user_name").where("id = 1").execute();
    cout<<myDocs.fetchOne()<<endl;
}


TEST_F(TestMysql,test_connect_str) {

    


    std::string usr("yedis");
    std::string pwd("123456");

    // Connect to MySQL Server on a network machine
    
    Client c("mysqlx://192.168.1.113:33060/yedis?user=yedis&password=123456");
    // Session mySession("mysqlx://192.168.1.113:33060/yedis?user=yedis&password=123456");
    // Client c("yedis:123456@192.168.1.113:33060/yedis",ClientOption::POOL_MAX_SIZE,10);
    Session mySession = c.getSession();

    // An alternative way of defining session settings.

    // SessionSettings settings(SessionOption::HOST,"localhost",
    //                      SessionOption::PORT, 33060);

    // settings.set(SessionOption::USER, usr);
    // settings.set(SessionOption::PWD, pwd);

    // Session mySession(settings);
    

    Schema db = mySession.getSchema("yedis");
    
    auto tb = db.getTable("user");
    auto myDocs = tb.select("user_name").where("id = 1").execute();
    cout<<myDocs.fetchOne()<<endl;
}


TEST_F(TestMysql,test_insert) {
    auto m = new Mysql();
    m->open("yedis:123456@192.168.1.113:33060/yedis");
    // m->insert("yedis","user",4,"sss");
    // m->insert("yedis","user","6","sss","2020-12-31 23:59:59");
}

TEST_F(TestMysql,test_lua) {
    lua_State* l = nullptr;
    
    yedis::LuaFactory::getFactory()->buildSlua(mysql_lua,[&l](lua_State* L) {        
            l = L;
    });

    yedis::LuaFactory::getFactory()->registerMysql(l);
    //call lua

    auto v = luabridge::getGlobal(l,"main");
    v();

    while(true) {
        sleep(1);
    }
}

#include "TestMyClient.h"
#include "MySqlclient.h"
#include <memory>
#include <string>

using namespace std;
using namespace yedis;




TEST_F(TestMyClient,test_connect) {
    auto c = new MySqlclient();
    const string host("192.168.1.113");
    const string user("yedis");
    const string pwd("123456");
    const string db("yedis");
    unsigned int port = 3306;
    c->connect(host,user,pwd,db,port);
    delete c;
    c = nullptr;
}


TEST_F(TestMyClient,test_query_select) {
    auto c = new MySqlclient();
    const string host("192.168.1.113");
    const string user("yedis");
    const string pwd("123456");
    const string db("employees");
    unsigned int port = 3306;
    c->connect(host,user,pwd,db,port);
    const string select("SELECT * FROM employees LIMIT 5;");
    while (true) {
        c->query(select);
        sleep(3);
    }
}

TEST_F(TestMyClient,test_create_table) {
    auto c = new MySqlclient();
    const string host("192.168.1.113");
    const string user("yedis");
    const string pwd("123456");
    const string db("employees");
    unsigned int port = 3306;
    c->connect(host,user,pwd,db,port);
    const string create("create table T(ID int primary key, c int);");
    ASSERT_EQ(0,c->crateTable(create));
}
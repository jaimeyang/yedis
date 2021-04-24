

#include "MySqlclient.h"
#include "mysql.h"
#include <iostream>

void yedis::MySqlclient::connect(const string &host, const string &user, const string &pwd, const string &db, unsigned int port) {
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql,host.c_str(),user.c_str(),pwd.c_str(),db.c_str(), 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
                mysql_error(&mysql));
        return;
    }
    cout<<"connect scuess"<<endl;
    return;
}

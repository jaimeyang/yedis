
#ifndef _MYSQL_CLIENT_H_
#define _MYSQL_CLIENT_H_

#include <string>
#include "mysql.h"

using namespace std;

namespace yedis
{
    class MySqlclient
    {
    public:
        MySqlclient(/* args */) = default;
        ~MySqlclient() = default;
        
        bool connect(const string &host, const string &user, const string &pwd, const string &db, unsigned int port);
        int crateTable(const string& sql);
        int createIndex(const string& sql);
        int query(const string& sql);
    private:
        /* data */
    private:    
        MYSQL m_mysql;
    };

}

#endif
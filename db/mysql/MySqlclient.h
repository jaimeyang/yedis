
#ifndef _MYSQL_CLIENT_H_
#define _MYSQL_CLIENT_H_

#include <string>

using namespace std;

namespace yedis
{
    class MySqlclient
    {
    public:
        MySqlclient(/* args */) = default;
        ~MySqlclient() = default;
        
        void connect(const string &host, const string &user, const string &pwd, const string &db, unsigned int port);

    private:
        /* data */
    private:
    };

}

#endif
#ifndef _MYSQL_H_
#define _MYSQL_H_

namespace yedis {
    class Mysql
    {    
    private:
        Mysql() = default;
        ~Mysql() = default;
    public:
        static Mysql* getMysql() {
            if (m_mysql == nullptr) {
                m_mysql = new Mysql();
            }
            return m_mysql;
        };
        
    private:
        static Mysql* m_mysql;
    };

}




#endif
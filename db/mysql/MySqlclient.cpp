

#include "MySqlclient.h"

#include <iostream>

bool yedis::MySqlclient::connect(const string &host, const string &user, const string &pwd, const string &db, unsigned int port) {
    cout<<"connect c"<<endl;
    mysql_init(&this->m_mysql);
    if (!mysql_real_connect(&this->m_mysql,host.c_str(),user.c_str(),pwd.c_str(),db.c_str(), 0, NULL, 0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n",
                mysql_error(&this->m_mysql));
        return false;
    }
    return true;
}

int yedis::MySqlclient::crateTable(const string& str) {
    auto ret = mysql_real_query(&this->m_mysql,str.c_str(),str.size());
    if (ret != 0) {
        cout<<"mysql crateTable is error "<<mysql_error(&this->m_mysql)<<endl;        
    }
    return ret;
}

int yedis::MySqlclient::createIndex(const string& sql) {
    auto ret = mysql_real_query(&this->m_mysql,sql.c_str(),sql.size());
    if (ret != 0) {
        cout<<"mysql createIndex is error "<<mysql_error(&this->m_mysql)<<endl;        
    }
    return ret;
}

int yedis::MySqlclient::query(const string& str) {
    auto ret = mysql_real_query(&this->m_mysql,str.c_str(),str.size());
    if (ret != 0) {
        cout<<"mysql query is error "<<mysql_error(&this->m_mysql)<<endl;
        return ret;
    }
    auto res = mysql_store_result(&this->m_mysql);
    
    // MYSQL_FIELD *field;

    // while((field = mysql_fetch_field(res))){
    //     cout<<"field is "<<field->name<<" type "<<field->type<<endl;
    // }

    // unsigned int num_fields = mysql_num_fields(res);

    // MYSQL_ROW row;
    // while (row = mysql_fetch_row(res)) {
    //     for (int i = 0; i < num_fields; i++) {
    //         cout<<""<<row[i]<<endl;
    //     }
    // }
    
    return ret;
}
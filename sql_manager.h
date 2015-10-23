//
// Created by ry on 10/23/15.
//

#ifndef AGHACKS_SQL_MANAGER_H
#define AGHACKS_SQL_MANAGER_H

#include <mysql++/mysql++.h>
#include <mysql_driver.h>
#include <string>

using std::string;

class sql_manager {
private:
    friend class sql_model;

    sql_manager();
    ~sql_manager();

    string& get_row_by_number(const int line);
    void insert_row(const string& column_name, const string& text_inserted);

    sql::mysql::MySQL_Driver*driver;
    sql::Connection*connection;

    const string database_address;
    const string database_username;
    const string database_password;
};


#endif //AGHACKS_SQL_MANAGER_H

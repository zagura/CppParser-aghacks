//
// Created by ry on 10/23/15.
//

#ifndef AGHACKS_SQL_MANAGER_H
#define AGHACKS_SQL_MANAGER_H

#include <mysql++/mysql++.h>
#include <mysql_driver.h>
#include <prepared_statement.h>
#include <statement.h>
#include <string>
#include <vector>
#include <memory>
#include <thread>


using std::string;
using std::unique_ptr;
using std::vector;

extern string split_with_char(vector<string> list, char character = {' '});

class sql_manager {
private:
    friend class sql_model;

    sql_manager();
    ~sql_manager();

    const string get_column_by_line_number(const string line, const string column_name, const string table_name);
    void insert_row(const string table_name,const vector<string>& column_name, const vector<string> &text_inserted);

    sql::mysql::MySQL_Driver*driver;
    sql::Connection*connection;

    const string database_address;
    const string database_username;
    const string database_password;
    const string database_name;
};


#endif //AGHACKS_SQL_MANAGER_H

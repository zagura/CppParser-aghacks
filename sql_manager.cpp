//
// Created by ry on 10/23/15.
//

#include "sql_manager.h"

sql_manager::sql_manager(): database_address{"localhost"}, database_username{"test_user"}, database_password{"123abc"} {

    driver = driver = sql::mysql::get_mysql_driver_instance();
    connection = driver -> connect(database_address,database_username,database_password);
}

sql_manager::~sql_manager() {
    delete connection;
}

//
// Created by ry on 10/23/15.
//

#include <resultset.h>
#include "sql_manager.h"

sql_manager::sql_manager(): database_address{"localhost"}, database_username{"test_user"}, database_password{"123abc"} {

    driver = driver = sql::mysql::get_mysql_driver_instance();
    connection = driver -> connect(database_address,database_username,database_password);
}

sql_manager::~sql_manager() {
    delete connection;
}

const string sql_manager::get_row_by_number(const string line) {
    unique_ptr<sql::Statement> statement {connection->createStatement()};
//    unique_ptr<sql::PreparedStatement> statement {
//            connection->prepareStatement("SELECT url FROM restaurants ORDER BY updated_at LIMIT ,1")};
    unique_ptr<sql::ResultSet> result { (statement->
            executeQuery("SELECT url FROM restaurants ORDER BY updated_at LIMIT "+line+",1"))}; //TO DEBUG
    return result->getString("url").asStdString();




}

void sql_manager::insert_row(const string &column_name, const string &text_inserted) {

}

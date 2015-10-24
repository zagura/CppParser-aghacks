//
// Created by ry on 10/23/15.
//

#include <resultset.h>
#include "sql_manager.h"

sql_manager::sql_manager(): database_address{"localhost"}, database_username{"test_user"}, database_password{"123abc"} {

    driver = sql::mysql::get_mysql_driver_instance();
    connection = driver -> connect(database_address,database_username,database_password);
}

sql_manager::~sql_manager() {
    delete connection;
}

const string sql_manager::get_column_by_line_number(const string line, const string column_name, const string table_name) {
    unique_ptr<sql::Statement> statement {connection->createStatement()};
    unique_ptr<sql::ResultSet> result { (statement->
            executeQuery("SELECT "+column_name+"FROM "+table_name+" ORDER BY updated_at LIMIT "+line+",1"))}; //TO DEBUG
    return result->getString("url").asStdString();
}

void sql_manager::insert_row(const string table_name,const vector<string>& column_name,
                             const vector<string>& text_inserted) {
//    INSERT INTO "+table_name+" ("+column_name+") VALUES (?)"
//                                   " ON DUPLCATE KEY UPDATE "+column_name+"=VALUES("+column_name+")"
    vector<string> values(column_name.size(),"?");
    string splitted_values = split_with_char(values, ',');
    string splitted_column_names = split_with_char(column_name,',');
    string statement_str = "INSERT INTO "+table_name+" ("+splitted_column_names+") VALUES ("+splitted_values+")"
                        " ON DUPLICATE KEY UPDATE "+splitted_column_names+"=VALUES("+splitted_column_names+")";
    unique_ptr<sql::PreparedStatement> statement {connection->prepareStatement
            (statement_str)};

    for(int i=0; i<text_inserted.size(); ++i) {
        statement->setString(i, text_inserted[i]);
    }
    statement->execute();
}

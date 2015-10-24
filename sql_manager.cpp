//
// Created by ry on 10/23/15.
//

#include <resultset.h>
#include "sql_manager.h"

sql_manager::sql_manager(): database_address{"localhost"}, database_username{"test_user"},
                            database_password{"123abc"}, database_name{"tanie_danie"} {

    driver = sql::mysql::get_mysql_driver_instance();
    driver->threadInit();
    connection = driver -> connect(database_address,database_username,database_password);
    connection->setSchema(database_name);
}

sql_manager::~sql_manager() {
    delete connection;
    driver->threadEnd();
}
const string sql_manager::get_column_by_line_number(const string line, const string column_name, const string table_name) {
    unique_ptr<sql::Statement> statement {connection->createStatement()};
    string statement_str {"SELECT "+column_name+" FROM "+table_name+" ORDER BY updated_at limit "+line+",1"};
    unique_ptr<sql::ResultSet> result { (statement->executeQuery(statement_str))};

    if(result->next())
        return result->getString(column_name);
    return "";
}

void sql_manager::insert_row(const string table_name,const vector<string>& column_name,
                             const vector<string>& text_inserted) {

    vector<string> values(column_name.size(), "?");
    string splitted_values = split_with_char(values, ',');
    string splitted_column_names = split_with_char(column_name, ',');

    string update_values_with_column_names = [&column_name]() -> string {
        string result;
        for (int i = 0; i < column_name.size() - 1; ++i)
            result += column_name[i] + "=VALUES(" + column_name[i] + "), ";
        result += column_name.back() + "=VALUES(" + column_name.back() + ") ";
        return result;
    }();

    string statement_str =
            "INSERT INTO " + table_name + " (" + splitted_column_names + ") VALUES (" + splitted_values + ")"
                    " ON DUPLICATE KEY UPDATE "
            + update_values_with_column_names;
    unique_ptr<sql::PreparedStatement> statement{connection->prepareStatement(statement_str)};

    for (unsigned int i = 1; i <= column_name.size(); ++i) {
        statement->setString(i, text_inserted[i - 1]);
    }
    statement->execute();
}

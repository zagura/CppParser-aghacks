//
// Created by ry on 10/23/15.
//

#include "sql_model.h"

mutex sql_model::get_url_lck{};
condition_variable sql_model::get_url_condition{};

sql_model::sql_model() : manager{sql_manager()}, row_counter{0}{
//    rows_number.store(update_rows_number());
    rows_number=(update_rows_number());
}


sql_model::~sql_model() {

}

string sql_model::get_next_url_address() {
    int line = row_counter;
    ++row_counter;
    string line_str = std::to_string(line);
    string result;

    try {
        result = manager.get_column_by_line_number(line_str, "url", "restaurants");
        std::cout << std::this_thread::get_id() << result; //remove
    } catch (mysqlpp::Exception e) {
        //Write e to log
    }
    return result;
}

bool sql_model::insert_formatted_text(const vector<string> &formatted_text) {
    return false;
}

bool sql_model::insert_unformatted_text(const string &unformatted_text) {
    return false;
}

int sql_model::update_rows_number() {
    return 0;
}
int sql_model::get_rows_number()
{
    return rows_number;
}


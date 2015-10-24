//
// Created by ry on 10/23/15.
//

#include "sql_model.h"


sql_model::sql_model() : manager{sql_manager()}, row_counter{0}{
    rows_number=(update_rows_number());
    static_assert(rows_number!=0, "Empty restaurants database");
}


sql_model::~sql_model() {

}

string sql_model::get_next_url_address() {
    int line = row_counter;
    update_rows_number();
    row_counter=(row_counter+1)%rows_number;

    string line_str = std::to_string(line);
    string result;

    try {
        result = manager.get_column_by_line_number(line_str, "url", "restaurants");
//        std::cout << std::this_thread::get_id() << result; //remove
    } catch (mysqlpp::Exception e) {
//        Write e to log
    }
    return result;
}

bool sql_model::insert_formatted_text(const vector<string> &formatted_text) {
    try {
        manager.insert_row("meals", vector<string>(formatted_text.size(), "desc"),formatted_text);
    } catch (mysqlpp::Exception e) {
//        Write e to log
    }
}

bool sql_model::insert_unformatted_text(const string &unformatted_text) {
    try {
        manager.insert_row("offers", vector<string>(unformatted_text.size(),"unformatted_text"), {unformatted_text});
    } catch (mysqlpp::Exception e) {
//        Write e to log
    }
}

int sql_model::update_rows_number() {
    string rows_number=manager.get_column_by_line_number("0", "COUNT(*)","restaurants" );
    int result = stoi(rows_number);
    return result;
}
int sql_model::get_rows_number()
{
    return rows_number;
}


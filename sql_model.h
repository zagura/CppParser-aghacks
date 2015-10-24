//
// Created by ry on 10/23/15.
//

#ifndef AGHACKS_SQL_MODEL_H
#define AGHACKS_SQL_MODEL_H

#include <string>
#include <atomic>
#include <vector>
#include "sql_manager.h"

using std::string;
using std::atomic;
using std::vector;

class sql_model {

public:
    sql_model();

    string& get_next_url_address(); //dodaj mutex
    bool insert_formatted_text(const vector<string>& formatted_text); //tez
    bool insert_unformatted_text(const string& unformatted_text); //tu tez
private:
    atomic<int> row_counter;
    atomic<int> current_rows_number;
    sql_manager manager;
};


#endif //AGHACKS_SQL_MODEL_H

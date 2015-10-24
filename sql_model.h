//
// Created by ry on 10/23/15.
//

#ifndef AGHACKS_SQL_MODEL_H
#define AGHACKS_SQL_MODEL_H

#include <string>
#include <atomic>
#include <vector>
#include <mutex>
#include <condition_variable>
#include "sql_manager.h"

using std::string;
using std::atomic;
using std::vector;
using std::mutex;
using std::unique_lock;
using std::condition_variable;

class sql_model {

public:
    sql_model();
    ~sql_model();
    string get_next_url_address(); //dodaj mutex
    bool insert_formatted_text(const vector<string>& formatted_text); //tez
    bool insert_unformatted_text(const string& unformatted_text); //tu tez
    int get_rows_number();
private:
    static mutex get_url_lck;
    static mutex insert_text_lck;
    static condition_variable get_url_condition;
    int update_rows_number();
    int row_counter;
    int rows_number;
    sql_manager manager;
};


#endif //AGHACKS_SQL_MODEL_H

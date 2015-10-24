//
// Created by ry on 10/24/15.
//

#include "functions.h"

string split_with_char(vector<string> list, char character) {
    string result;
    auto penultimate_it = --list.end();

    for(auto x=list.begin(); x<penultimate_it ;++x) {
        result+=(*x)+",";
    }
    result+=*penultimate_it;
    return result;
}

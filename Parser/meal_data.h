//
// Created by misiek on 24.10.15.
//

#ifndef AGHACKS_MEAL_DATA_H
#define AGHACKS_MEAL_DATA_H
#include <string>

using std::string;

class meal_data {
private:
    string description;
    string unprepared_text;
    pair<string, vector<string> > get_data();
};


#endif //AGHACKS_MEAL_DATA_H

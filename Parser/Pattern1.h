//
// Created by misiek on 24.10.15.
//

#ifndef AGHACKS_PATTERN1_H
#define AGHACKS_PATTERN1_H

#include <regex>
#include <string>

using std::string;

//Pattern1 for parsing from:
//              http://www.piurestauracja.pl/dania-dnia-na-caly-tydzien/
class Pattern1 {
    Pattern1();
    Pattern1(string content);

    ~Pattern1();
};


#endif //AGHACKS_PATTERN1_H

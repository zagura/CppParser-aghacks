//
// Created by misiek on 24.10.15.
//

#ifndef AGHACKS_PARSER_H
#define AGHACKS_PARSER_H
#include <string>
#include <vector>

using std::vector;
using std::string;

class parser {
public:
    parser(string content) {};
//    string get_unformatted_text();
//    vector <string> get_meals();
//    ~parser();
    void parse_html(string text);
};


#endif //AGHACKS_PARSER_H

//
// Created by ry on 10/24/15.
//

#ifndef AGHACKS_AI_PARSER_H
#define AGHACKS_AI_PARSER_H

#include <regex>
#include <vector>
#include <fstream>
#include <string>

using std::regex;
using std::regex_match;
using std::regex_search;
using std::regex_replace;
using std::smatch;
using std::vector;
using std::string;

#include "parser.h"

class ai_parser :public parser {
public:
    ai_parser(string& content);

    string& get_text();
private:
    void parse_offer();
    void remove_all_html();

    string text;
    vector<regex> keywords_patterns;
    vector<regex> all_tags;
    vector<regex> relevant_tags;


};


#endif //AGHACKS_AI_PARSER_H

//
// Created by ry on 10/24/15.
//

#include "ai_parser.h"
#include <iostream>

ai_parser::ai_parser(string& content): parser(content), text{content} {
    std::ifstream ifs1("Parser/keywords.txt", std::ios_base::in);

    if(ifs1.is_open()) {
        for(string line; ifs1.good(); ) {
            getline(ifs1, line);
                keywords_patterns.push_back(regex{line});
        }
        ifs1.close();
    }
    std::ifstream ifs2("Parser/relevanttags.txt", std::ios_base::in);

    if(ifs2.is_open()) {
        for(string line; ifs2.good(); ) {
            getline(ifs2, line);
            relevant_tags.push_back(regex{line});
        }
        ifs2.close();
    }
    std::ifstream ifs3("Parser/alltag.txt", std::ios_base::in);

    if(ifs3.is_open()) {
        for(string line; ifs3.good(); ) {
            getline(ifs3, line);
            all_tags.push_back(regex{line});
        }
        ifs3.close();
    }
    parse_offer();
    remove_all_html();
}

void ai_parser::parse_offer() {
    //wybierz tylko te teksty ktore sa pomiedzy relevant tags
    smatch matches;
    string result;
    string tmp=text;
    for(auto x:relevant_tags) {
        text=tmp;
        while(regex_search(text, matches, x)) {
            if (matches[1].matched) {
                result += matches[1].str()+"\n";
                text=matches.suffix().str();
            }
        }
    }
    text=result;
}

void ai_parser::remove_all_html() {
    string result=text;
    string format("");
    for(int i=0; i<all_tags.size(); ++i) {
        result = regex_replace(result,all_tags[i],format);
    }
    text=result;
}

string &ai_parser::get_text() {
    return text;
}

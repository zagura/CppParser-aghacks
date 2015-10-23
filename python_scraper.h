//
// Created by ry on 10/23/15.
//

#ifndef AGHACKS_PYTHON_SCRAPER_H
#define AGHACKS_PYTHON_SCRAPER_H

#include <python2.7/Python.h>
#include <string>

using std::string;

class python_scraper {
public:
    python_scraper(char* name, char* func, char* link);
    ~python_scraper();
private:
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pLink, *pValue;

    string scrape();



};


#endif //AGHACKS_PYTHON_SCRAPER_H

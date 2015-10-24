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
    python_scraper(const char* link);
    ~python_scraper();
    string scrape();
private:
    PyObject *pName, *pModule, *pDict, *pFunc;
    PyObject *pLink, *pValue;





};


#endif //AGHACKS_PYTHON_SCRAPER_H

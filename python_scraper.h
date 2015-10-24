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
    python_scraper(const char* name,const char* func,const char* link);
    //name: python script name
    //func: python calling function name
    //link: link given as an argument to python function
    ~python_scraper();
    string scrape();
private:
    PyObject *pModule, *pFunc;
    PyObject *pLink, *pResult;
    PyObject *pArg;

};
namespace exception_scraper {
    class scraper_exception {
    public:
        string message;
        string details;

        scraper_exception() { };
        scraper_exception(string d, string m = static_cast<string>("None")): message(m), details(d){};
        scraper_exception(void* v, string m = static_cast<string>("Unknown exception")){
            if (v == NULL) {
                details = "null pointer";
            }
            else {
                details="Critical error!";
            }
        };
    };

    class bad_name : public scraper_exception {
    public:
        bad_name(string d):scraper_exception(d,static_cast<string>("Bad name exception")){};
        bad_name(void* v):scraper_exception(v,static_cast<string>("Bad name exception")){};
    };

    class bad_module : public scraper_exception {
    public:
        bad_module(string d):scraper_exception(d,static_cast<string>("Bad module exception")){};
        bad_module(void* v):scraper_exception(v,static_cast<string>("Bad module exception")){};
    };
    class bad_function : public scraper_exception{
    public:
        string message = static_cast<string>("Bad function exception");
        bad_function(string d):scraper_exception(d, static_cast<string>("Bad function exception")){};
        bad_function(void* v):scraper_exception(v, static_cast<string>("Bad function exception")){};
    };

}
#endif //AGHACKS_PYTHON_SCRAPER_H

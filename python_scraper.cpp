//
// Created by ry on 10/23/15.
//

#include "python_scraper.h"

python_scraper::python_scraper(const char *link) {
    Py_Initialize();
    char program_name[] = "getpage.py";
    Py_SetProgramName(program_name);
    PyObject* sysPath = PySys_GetObject((char*)"path");
    PyList_Append(sysPath, PyString_FromString("."));
    PyObject* pName = PyString_FromString(name);
    if(pName == NULL) throw exception_scraper::bad_name(pName);
    this->pModule = PyImport_Import(pName);
    if(pModule == NULL) throw exception_scraper::bad_module((void*)pModule);
    this->pFunc = PyObject_GetAttrString(pModule, func);
    if(pFunc == NULL) throw exception_scraper::bad_function(pFunc);
    if(!PyCallable_Check(pFunc)) throw exception_scraper::bad_function("Can't call this function");
    this->pLink = PyString_FromString(link);
    pArg = PyTuple_New(1);
    PyTuple_SetItem(pArg, 0, pLink);
}
string python_scraper::scrape() {
    this->pResult = PyObject_CallObject(pFunc, pArg);
    if(pResult == NULL){
        PyErr_Print();
    throw exception_scraper::scraper_exception("null pointer", "Unknown result");
    }
    return PyString_AsString(pResult);
}
python_scraper::~python_scraper() {
    Py_XDECREF(pResult);
    Py_XDECREF(pLink);
    Py_XDECREF(pFunc);
    Py_DECREF(pModule);

    Py_Finalize();
    Py_XDECREF(pModule);
}
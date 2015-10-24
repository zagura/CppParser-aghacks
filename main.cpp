#include <iostream>
#include "python_scraper.h"

using std::cout;
using std::endl;

int main() {
    try{
        python_scraper ps("getpage", "readIt", "http://www.aghacks.com");
        cout<<ps.scrape();
    }catch(exception_scraper::scraper_exception e){
        cout<<e.message<<endl;
        cout<<e.details<<endl;
    }
    return 0;
}
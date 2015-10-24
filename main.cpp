#include <iostream>
#include <vector>
#include <string>
#include "sql_manager.h"
#include "sql_model.h"
#include "python_scraper.h"
#include <thread>
#include <future>
#include <chrono>
#include <queue>
#include <condition_variable>
#include <mutex>

using namespace std;
using namespace std::chrono;


void acquire_url();
void load_url_address();
void scrape_webpage(const char* link );


queue<string> url_addresses{};
condition_variable url_condition;
mutex url_mutex;

void load_url_address()
{
    static int counter;
    sql_model model;
    while(true) {
        string result = model.get_next_url_address();       //model->connect()
        unique_lock<mutex> lock {url_mutex};
        url_addresses.push(result);
        ++counter;
        int b = url_addresses.size(); // temp
        lock.unlock();
        url_condition.notify_one();
        //int size = url_addresses.size();
       // while(size >= model.get_rows_number()) {
        //    size=url_addresses.size();
        //    url_condition.wait(lock);
//            url_condition.notify_one();
        if(counter == model.get_rows_number()) {
            counter =0 ;
            this_thread::sleep_for(seconds(10));  //model->disconnect()
        }
       // }
    }

}
void acquire_url() {
    string url;
    while (true) {
        unique_lock<mutex> lock{url_mutex};
        while (url_addresses.empty()) {
            url_condition.wait(lock);
        }
        url = url_addresses.front();
        url_addresses.pop();
//            if(lock.owns_lock()) {
        lock.unlock();
//            }
      //  url_condition.notify_one();
        //thread t(scraperewebpage)
        // t.detach;
        scrape_webpage(url.c_str());
    }
}

void scrape_webpage(const char* link)
{
     string str = link;
     python_scraper scraper(str.c_str());
     string result = scraper.scrape();
    cout << result << endl;
    //call parser(result)
}

int main(int argc, char** argv)
{

//    thread t1 {load_url_address};
//    this_thread::sleep_for(std::chrono::milliseconds(300));
//    thread t2 {acquire_url};
//    t1.join();
//    t2.join();
    sql_model model;
    model.
//    char* name = "http://www.google.pl";
//    python_scraper scraper(name);
//    scraper.scrape();
    return 0;
}

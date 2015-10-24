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
    static sql_model model;
    while(true) {
        string result = model.get_next_url_address();
        unique_lock<mutex> lock {url_mutex};
        url_addresses.push(result);
        lock.unlock();
        url_condition.notify_one();
        while(url_addresses.size() >= model.get_rows_number()) {
            url_condition.wait(lock);
        }
    }

}
void acquire_url()
{
    string url;
    while(true) {
        unique_lock<mutex> lock{url_mutex};
        while(url_addresses.empty()) {
                url_condition.wait(lock);
        }
            url = url_addresses.front();
            url_addresses.pop();
//            if(lock.owns_lock()) {
                lock.unlock();
//            }
            url_condition.notify_one();

        thread t {&scrape_webpage, url.c_str()};
        t.detach();
    }
}
void scrape_webpage(const char* link)
{
    string str = link;
    python_scraper scraper(str.c_str());
    string result = scraper.scrape();

    //call parser(result)
}

int main(int argc, char** argv)
{

    thread t1 {load_url_address};
    this_thread::sleep_for(std::chrono::milliseconds(300));
    thread t2 {acquire_url};
    t1.join();
    t2.join();

    return 0;
}

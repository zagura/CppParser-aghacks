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
void scrape_webpage();


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
        url_condition.notify_one();
        if(url_addresses.size() >= model.get_rows_number()) {
            url_condition.wait(lock);
        }
    }

}
void acquire_url()
{
    string url;
    while(true) {
        unique_lock<mutex> lock{};
        while(url_addresses.empty()) {
            url_condition.wait(lock);
        }
            url = url_addresses.front();
            url_addresses.pop();
            lock.unlock();
            url_condition.notify_one();

//        thread t {scrape_webpage, url.c_str()};
    }
}
void scrape_webpage(const char* link )
{
    python_scraper scraper(link);
    string result = scraper.scrape();
}

int main(int argc, char** argv)
{

//    while(true) {
//        promise<string> url_promise;
//        auto url_future = url_promise.get_future();
//        thread url_thread {get_url_address, url_promise};
//        url_thread.join();
//        string url_result = url_future.get();
//
//        promise<string> scraper_promise;
//        auto scraper_future = scraper_promise.get_future();
//        thread scraper_thread {scrape_webpage, argv[1], argv[2],url_result};
//
//        this_thread::sleep_for(duration_cast<milliseconds>(seconds(4)));
//
//    }

    return 0;
}


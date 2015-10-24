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
#include "Parser/parser.h"
#include "Parser/ai_parser.h"

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
    char*link="http://www.biesiada-krakow.pl";
    python_scraper scraper(link);
    string result = scraper.scrape();
//    cout << result;
//    string result = "<h1>\n"
//            "\t\t\t\t\t\t<p>Witamy na naszej stronie</p>\n"
//            "</h1><p>Miło jest nam Państwa powitać w <strong>PIU RESTAURACJA &#038; PIZZERIA</strong></p>\n"
//            "<p>Stary Płaszów – Rybitwy.</p>\n"
//            "<p>Dołożymy wszelkich starań, aby na Państwa twarzach zagościł uśmiech. Zaskoczymy Państwa wspaniałym smakiem i świeżością naszych potraw oraz miłą, ponadprzeciętną obsługą. Dysponujemy salą dla około 35 osób w której jesteśmy w stanie zorganizować:</p>\n"
//            "<ul>\n"
//            "<li>Chrzciny, komunie</li>\n"
//            "<li>Przyjęcia imieninowe, urodzinowe</li>\n"
//            "<li>Urodziny dla maluchów (również z animatorem)</li>\n"
//            "<li>Spotkania firmowe (małe szkolenia, prezentacje itp.)</li>\n"
//            "<li>Spotkania wigilijne</li>\n"
//            "<li>Kompleksowo organizujemy catering (szczegóły w zakładce „przyjęcia okolicznościowe” i „dla firm”).</li>\n"
//            "</ul>\n"
//            "<p>Jesteśmy do Państwa dyspozycji.</p>\n"
//            "<p>Zapraszamy</p>";
    ai_parser par(result);
    cout << par.get_text();
    return 0;
}
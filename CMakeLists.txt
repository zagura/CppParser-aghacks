cmake_minimum_required(VERSION 2.8)
project(aghacks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/python2.7 -lpython2.7")

set(SOURCE_FILES main.cpp python_scraper.cpp python_scraper.h)
add_executable(aghacks ${SOURCE_FILES})

target_link_libraries(aghacks python2.7)


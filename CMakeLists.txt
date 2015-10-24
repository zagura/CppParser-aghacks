cmake_minimum_required(VERSION 3.3)
project(aghacks)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -I/usr/include/mysql++ -I/usr/include/mysql -I/usr/include/cppconn -I/usr/include/python2.7 -I/usr/include/mysqlcppconn -L/usr/lib/mysqlcppconn -lmysqlpp -lmysqlcppconn  -lpython2.7")

set(SOURCE_FILES main.cpp python_scraper.cpp python_scraper.h sql_manager.cpp sql_manager.h sql_model.cpp sql_model.h functions.cpp functions.h)
add_executable(aghacks ${SOURCE_FILES})

target_link_libraries(aghacks mysqlcppconn python2.7)



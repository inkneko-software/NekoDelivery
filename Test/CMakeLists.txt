cmake_minimum_required(VERSION 3.5)
set(NOTEST test.cpp)

add_executable(noTest ${NOTEST})
target_link_libraries(noTest dao_mysql)
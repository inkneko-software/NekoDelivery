cmake_minimum_required(VERSION 3.5)

add_subdirectory(dao)

set(GTEST_LIB_DIR /usr/local/lib/)
set(GTEST_INCLUDE_DIR /usr/local/include)
link_directories(${GTEST_LIB_DIR})
include_directories(BEFORE ${GTEST_INCLUDE_DIR})
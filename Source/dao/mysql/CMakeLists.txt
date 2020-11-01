cmake_minimum_required(VERSION 3.5)

aux_source_directory(. SOURCE_DIR_MYSQL_DAO_WARP)
add_library(dao_mysql ${SOURCE_DIR_MYSQL_DAO_WARP})

set(MYSQL_LIB_DIR /usr/lib/x86_64-linux-gnu)
set(MYSQL_INCLUDE_DIR /usr/include)
link_directories(${MYSQL_LIB_DIR})
include_directories(BEFORE ${MYSQL_INCLUDE_DIR})

target_link_libraries (dao_mysql mysqlcppconn)
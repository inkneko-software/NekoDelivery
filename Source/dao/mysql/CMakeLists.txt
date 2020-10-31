cmake_minimum_required(VERSION 3.5)

aux_source_directory(. SOURCE_DIR_MYSQL_DAO_WARP)
add_library(dao_mysql ${SOURCE_DIR_MYSQL_DAO_WARP})

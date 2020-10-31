cmake_minimum_required(VERSION 3.5)
aux_source_directory(. SOURCE_DIR_USER_DAO)
add_subdirectory(impl)
add_subdirectory(table)

#add_library(dao_user ${SOURCE_DIR_USER_DAO})
cmake_minimum_required(VERSION 3.5)

aux_source_directory(. SOURCE_DIR_USER_DAO_IMPL)
add_library(dao_user_impl ${SOURCE_DIR_USER_DAO_IMPL})
target_link_libraries(dao_user_impl dao_mysql)
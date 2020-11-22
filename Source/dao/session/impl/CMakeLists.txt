cmake_minimum_required(VERSION 3.5)
aux_source_directory(. SOURCE_DIR_SESSION_DAO_IMPL)
add_library(dao_session_impl ${SOURCE_DIR_SESSION_DAO_IMPL})
target_link_libraries(dao_session_impl dao_mysql ${USR_LIB}/libwebstring.so)
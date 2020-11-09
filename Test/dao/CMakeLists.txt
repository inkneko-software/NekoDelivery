add_subdirectory(mysql)

aux_source_directory(. SOURCE_DIR)
set(MYSQL_TEST_DIR ./mysql)

add_executable(test_dao ${SOURCE_DIR})
include_directories(test_dao ${MYSQL_TEST_DIR})
target_link_libraries(test_dao gtest pthread dao_mysql dao_user_impl)
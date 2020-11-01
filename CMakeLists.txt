cmake_minimum_required(VERSION 3.5)
project(NekoDelivery)
add_subdirectory(Source)
add_subdirectory(Test)

enable_testing()
add_test(NAME DAO_TEST COMMAND test_dao)
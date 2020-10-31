cmake_minimum_required(VERSION 3.5)
project(NekoDelivery)
add_subdirectory(Source)
add_subdirectory(Test)

enable_testing()
add_test(NAME noneTest COMMAND noTest)
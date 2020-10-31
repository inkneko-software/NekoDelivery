cmake_minimum_required(VERSION 3.5)

add_subdirectory(user)
add_subdirectory(mysql)

#target_link_libraries(NekoDeliveryDao dao_mysql dao_user_impl)
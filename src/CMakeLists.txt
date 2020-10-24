cmake_minimum_required (VERSION 3.5)
project(NekoDelivery)
set (CMAKE_CXX_STANDARD 11)
aux_source_directory (. SOURCE_NEKO_DELIVERY)
add_executable (NekoDelivery ${SOURCE_NEKO_DELIVERY})

#tinyHttpd dependence
set(USR_DIR /usr/local) #see lib/tinyHttpd/README.md
include_directories(BEFORE ${USR_DIR}/include/tinyHttpd)
target_link_libraries (NekoDelivery  ${USR_DIR}/lib/libtinyHttpd.so)

#config files
add_custom_command(TARGET NekoDelivery POST_BUILD 
COMMAND cp "${CMAKE_SOURCE_DIR}/conf/setting.conf" "${CMAKE_BINARY_DIR}/"
COMMAND cp "${CMAKE_SOURCE_DIR}/conf/mime.types" "${CMAKE_BINARY_DIR}/"
)


aux_source_directory(. SOURCE_DIR_AUTH)
add_executable(nekodelivery_auth ${SOURCE_DIR_AUTH})
#tinyHttpd dependence
set(USR_DIR /usr/local) #see lib/tinyHttpd/README.md
include_directories(BEFORE ${USR_DIR}/include/tinyHttpd)
target_link_libraries (nekodelivery_auth  ${USR_DIR}/lib/libtinyHttpd.so)
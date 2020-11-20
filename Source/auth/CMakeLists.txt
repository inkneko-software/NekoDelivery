aux_source_directory(. SOURCE_DIR_AUTH)
add_executable(nekodelivery_auth ${SOURCE_DIR_AUTH})
#tinyHttpd dependence
set(USR_LOCAL /usr/local)
include_directories(BEFORE ${USR_LOCAL}/include/)
link_directories(/usr/lib/x86_64-linux-gnu)

target_link_libraries (nekodelivery_auth  ${USR_LOCAL}/lib/libtinyHttpd.so boost_regex boost_system dao_user_impl)
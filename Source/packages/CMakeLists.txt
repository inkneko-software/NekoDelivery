aux_source_directory(. SOURCE_DIR_AUTH)
add_executable(nekodelivery_auth ${SOURCE_DIR_AUTH})
#tinyHttpd dependence
include_directories(BEFORE ${USR_INCLUDE})
link_directories(/usr/lib/x86_64-linux-gnu)

set(USR_LIB /usr/local/lib)
target_link_libraries (
	nekodelivery_auth  
	${USR_LIB}/libtinyHttpd.so
	boost_regex boost_system 
	dao_user_impl 
	nekodelivery_session
)
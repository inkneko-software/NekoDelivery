aux_source_directory(. SOURCE_DIR_SESSION)
add_library(nekodelivery_session ${SOURCE_DIR_SESSION})

include_directories(BEFORE ${USR_INCLUDE})
target_link_libraries (nekodelivery_session  ${USR_LIB}/libwebstring.so dao_session_impl)
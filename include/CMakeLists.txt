#Scan for headers and add them for installation
file(GLOB_RECURSE GCCPHAT_ALL_INCLUDES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)

message(STATUS "HEADER FILES: ${GCCPHAT_ALL_INCLUDES}")

add_custom_target(gccphat_headers SOURCES ${GCCPHAT_ALL_INCLUDES})

install(FILES ${GCCPHAT_ALL_INCLUDES} DESTINATION include)
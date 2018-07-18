project(GCCPHAT)
cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

#Add base directory for includes (global)
include_directories(include/gccphat)

add_subdirectory(include)

set(SRC

    src/utils/fft.c
    src/utils/matrix.c
    src/utils/svd.c

)

add_library(gccphat SHARED
	${SRC}
)

target_link_libraries(gccphat
	m
)

add_executable(demo
    demo/main.c
)
target_link_libraries(demo
    gccphat
)

install(TARGETS gccphat DESTINATION lib)
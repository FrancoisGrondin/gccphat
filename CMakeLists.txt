project(GCCPHAT)
cmake_minimum_required(VERSION 2.4.6)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PC_FFTW3 REQUIRED fftw3f)

include_directories("${PROJECT_SOURCE_DIR}/include")

set(CMAKE_BUILD_TYPE "Release")

set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/bin")
set(LIBRARY_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/lib")

#Add base directory for includes (global)
include_directories(include/gccphat_fft)
include_directories(include/gccphat_mm)
include_directories(include/gccphat_svd)

#add_subdirectory(include)

set(SRC_FFT
	src/gccphat_fft/utils/gpfft.c
	src/gccphat_fft/utils/gpfftqi.c
)
set(SRC_MM
	src/gccphat_mm/utils/gpmm.c
)
set(SRC_SVD
	src/gccphat_svd/utils/gpsvd.c
	src/gccphat_svd/utils/matrix.c
	src/gccphat_svd/utils/svd.c
)

add_library(gccphat_fft SHARED
	${SRC_FFT}
)
add_library(gccphat_mm SHARED
	${SRC_MM}
)
add_library(gccphat_svd SHARED
	${SRC_SVD}
)

target_link_libraries(gccphat_fft
	${PC_FFTW3_LIBRARIES}
	m
)
target_link_libraries(gccphat_mm
	m
)
target_link_libraries(gccphat_svd
	m
)

add_executable(simulate
	demo/simulate.c
)
target_link_libraries(simulate
	m
)

add_executable(gccphat
    demo/gccphat.c
)
target_link_libraries(gccphat
    gccphat_fft
    gccphat_mm
    gccphat_svd
)

install(TARGETS gccphat_fft DESTINATION lib)
install(TARGETS gccphat_mm DESTINATION lib)
install(TARGETS gccphat_svd DESTINATION lib)
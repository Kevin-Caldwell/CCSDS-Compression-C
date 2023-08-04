cmake_minimum_required(VERSION 3.0.0)
project(CCSDS_Compression VERSION 0.1.0 LANGUAGES C)
#find_package( OpenCV REQUIRED )


include(CTest)
enable_testing()

include_directories(include)

file(GLOB C_FILES "./src/**.c")

add_executable(CCSDS_Compression main.c ${C_FILES})
#include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#target_link_libraries(CCSDS_Compression ${OpenCV_LIBS} )

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(CCSDS_Compression PUBLIC ${MATH_LIBRARY})
endif()
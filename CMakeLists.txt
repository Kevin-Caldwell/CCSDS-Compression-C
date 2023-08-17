cmake_minimum_required(VERSION 3.0.0)
project(CCSDS_Compression VERSION 0.1.0 LANGUAGES C)


include(CTest)
enable_testing()

include_directories(include)

file(GLOB C_FILES "./src/**.c")

add_executable(CCSDS_Compression src/main.c ${C_FILES})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
#set(EXECUTABLE_OUTPUT_PATH "../")


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(CCSDS_Compression PUBLIC ${MATH_LIBRARY})
endif()
cmake_minimum_required(VERSION 3.0.0)
project(CCSDS_Compression VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

add_executable(CCSDS_Compression main.c src/image.c src/generate_image.c)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

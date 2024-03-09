cmake_minimum_required(VERSION 3.0.0)
project(CCSDS_Compressor VERSION 0.1.0 LANGUAGES C)
project(CCSDS_Image_Generator VERSION 0.1.0 LANGUAGES C)
project(CCSDS_Decompressor VERSION 0.1.0 LANGUAGES C)


include(CTest)
enable_testing()

include_directories(include)

file(GLOB C_FILES "./src/**.c")

add_executable(CCSDS_Compressor main/compressor.c ${C_FILES})
add_executable(CCSDS_Image_Generator main/image_handler.c ${C_FILES})
add_executable(CCSDS_Decompressor main/decompressor.c ${C_FILES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(CCSDS_Image_Generator PUBLIC ${MATH_LIBRARY})
    target_link_libraries(CCSDS_Compressor PUBLIC ${MATH_LIBRARY})
    target_link_libraries(CCSDS_Decompressor PUBLIC ${MATH_LIBRARY})
endif()

add_compile_definitions(MEMORY_SAVING)
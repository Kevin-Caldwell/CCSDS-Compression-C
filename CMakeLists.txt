cmake_minimum_required(VERSION 3.0.0)
project(CCSDS_Compression VERSION 0.1.0 LANGUAGES C)
#find_package( OpenCV REQUIRED )


include(CTest)
enable_testing()

include_directories(include)

add_executable(CCSDS_Compression 
            main.c 
            src/constants.c
            src/image_instance.c
            src/generate_image.c
            src/image.c
            src/linear_algebra.c
            src/local_differences.c
            src/local_sum.c
            src/predictor.c
            src/quantizer.c
            src/sample_representative.c
            src/weights.c)
#include_directories( ${OpenCV_INCLUDE_DIRS} )

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#target_link_libraries(CCSDS_Compression ${OpenCV_LIBS} )


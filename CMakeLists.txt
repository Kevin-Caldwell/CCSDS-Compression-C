cmake_minimum_required(VERSION 3.22.1)

project(CCSDS_Image_Generator VERSION 0.1.0 LANGUAGES C ASM)
project(CCSDS_Compressor VERSION 0.1.0 LANGUAGES C ASM)
project(CCSDS_Decompressor VERSION 0.1.0 LANGUAGES C ASM)


set(ARM_COMPILE 0)

if(ARM_COMPILE)
    add_compile_definitions(ARM_COMPILE)
    set(CMAKE_VERBOSE_MAKEFILE ON)
    set(CMAKE_C_STANDARD 99)
    set(CMAKE_SYSTEM_NAME           Generic)
    set(CMAKE_SYSTEM_PROCESSOR      arm)
    set(CMAKE_C_COMPILER            arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER          arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER          arm-none-eabi-as)
    set(CMAKE_LINKER                arm-none-eabi-ld)
    add_compile_options(-mcpu=cortex-m7 -mthumb -mfpu=fpv5-sp-d16 -mfloat-abi=hard -Wall -Og -specs=nosys.specs --specs=nosys.specs)
endif()

add_compile_definitions(STM32H743xx)

# Add all C files in src and set the include path
include_directories(include)
file(GLOB C_FILES "./src/**.c")

# Make Separate Executables for Compressor, Decompressor and Image Analysis
add_executable(CCSDS_Image_Generator    main/image_handler.c    ${C_FILES})
add_executable(CCSDS_Compressor         main/compressor.c       ${C_FILES})
add_executable(CCSDS_Decompressor       main/decompressor.c     ${C_FILES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# Math Library Include
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(CCSDS_Image_Generator PUBLIC ${MATH_LIBRARY})
    target_link_libraries(CCSDS_Compressor PUBLIC ${MATH_LIBRARY})
    target_link_libraries(CCSDS_Decompressor PUBLIC ${MATH_LIBRARY})
endif()

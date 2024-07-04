cmake_minimum_required(VERSION 3.22.1)

project(hc-imgen        VERSION 0.1.0 LANGUAGES C ASM)
project(hc-compress     VERSION 0.1.0 LANGUAGES C ASM)
project(hc-decompress   VERSION 0.1.0 LANGUAGES C ASM)


set(ARM_COMPILE 0)
# set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_C_STANDARD 99)
set(CMAKE_SYSTEM_NAME           Generic)


if(ARM_COMPILE)
    add_compile_definitions(STM32H743xx)
    add_compile_definitions(ARM_COMPILE)
    set(CMAKE_SYSTEM_PROCESSOR      arm)
    set(CMAKE_C_COMPILER            arm-none-eabi-gcc)
    set(CMAKE_CXX_COMPILER          arm-none-eabi-g++)
    set(CMAKE_ASM_COMPILER          arm-none-eabi-as)
    set(CMAKE_LINKER                arm-none-eabi-ld)
    add_compile_options(
        -mcpu=cortex-m7 
        -march=armv7e-m+fp+fpv5+fp.dp 
        -mtune=cortex-m7 
        -mthumb 
        -mfpu=fpv4-sp-d16 
        -mfloat-abi=hard 
        -Wall 
        -Og 
        --specs=nosys.specs 
        -Wextra 
        -ffunction-sections 
        -fdata-sections 
        -ffreestanding 
        -flto
        -g
    )

    add_link_options(77
        -g 
        -W 
        -lgcc 
        -nostdlib 
        -lm)
    
else()
    set(CMAKE_C_COMPILER            gcc-12)

endif()


# Add all C files in src and set the include path
include_directories(include)
file(GLOB C_FILES "./src/**.c")

# Make Separate Executables for Compressor, Decompressor and Image Analysis
add_executable(hc-imgen             main/image_handler.c    ${C_FILES})
add_executable(hc-compress          main/compressor.c       ${C_FILES})
add_executable(hc-decompress        main/decompressor.c     ${C_FILES})


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)


# Math Library Include
find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(hc-imgen PUBLIC ${MATH_LIBRARY})
    target_link_libraries(hc-compress PUBLIC ${MATH_LIBRARY})
    target_link_libraries(hc-decompress PUBLIC ${MATH_LIBRARY})
endif()

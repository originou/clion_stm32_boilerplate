cmake_minimum_required(VERSION 3.12)
project(stm32_dma_workspace CXX C)
set(CMAKE_VERBOSE_MAKEFILE OFF)
# setup toolchain
# Use default toolchain if not define your own by -DCMAKE_TOOLCHAIN_FILE=/your/own/path
if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    message(STATUS "CMAKE_TOOLCHAIN_FILE not defined, use default one cmake/toolchain.cmake")
    set(CMAKE_TOOLCHAIN_FILE "cmake/toolchain.cmake" CACHE PATH "toolchain file")
    include(${CMAKE_TOOLCHAIN_FILE})
else ()
    message(STATUS "CMAKE_TOOLCHAIN_FILE is defined, use ${CMAKE_TOOLCHAIN_FILE}")
endif ()

# Set the C/C++ Standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

message("----------- STANDARD CONFIGURATION------------")
message(STATUS "C STANDARD: ${CMAKE_C_STANDARD}")
message(STATUS "CXX STANDARD: ${CMAKE_CXX_STANDARD}")

# Include libopencm3
include(cmake/libopencm3.cmake)

# Include freeRTOS
include(cmake/freertos.cmake)

# Devices profiles
include(cmake/devices.cmake)

# Compiler
include(cmake/compiler.cmake)

set(OUTPUT_DIR ${PROJECT_SOURCE_DIR}/build/${STM32_DEVICE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIR})

# custom target
add_custom_target(libopencm3 make TARGETS=${LIBOPENCM3_BUILD_TARGET} WORKING_DIRECTORY ${LIBOPENCM3_DIR})

# add workspace
add_subdirectory(workspace)


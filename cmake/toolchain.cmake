message(STATUS "TOOL CHAIN CMAKE CONFIGURATION")
# Use ARM-GCC for crosscompiling
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

if (NOT DEFINED TOOLCHAIN_DIR)
    message(STATUS "TOOLCHAIN_DIR is not defined, will find compiler programs by PATH.")

endif ()

find_program(ARM_CC arm-none-eabi-gcc ${TOOLCHAIN_DIR})
find_program(ARM_CXX arm-none-eabi-g++ ${TOOLCHAIN_DIR})
find_program(ARM_OBJCOPY arm-none-eabi-objcopy ${TOOLCHAIN_DIR})
find_program(ARM_SIZE arm-none-eabi-size ${TOOLCHAIN_DIR})

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER ${ARM_CC})
set(CMAKE_CXX_COMPILER ${ARM_CXX})
set(CMAKE_ASM_COMPILER ${ARM_CC})
set(OBJCOPY ${ARM_OBJCOPY})

message(STATUS "DEFAULT OBJCOPY: ${OBJCOPY}")

set(CMAKE_CONFIGURATION_TYPES "stm32f103_bluepill;stm32f4_black" CACHE STRING "" FORCE)
# Set STM32 SoC specific variables

message("-----------Device Information------------")
if((NOT DEFINED CMAKE_BUILD_TYPE) OR ("${CMAKE_BUILD_TYPE}" STREQUAL ""))
    message(STATUS "CMAKE_BUILD_TYPE not defined, Debug will be set.")
    set(CMAKE_BUILD_TYPE Debug)
endif()
link_directories(${CMAKE_SOURCE_DIR}/ld/stm32)

message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
if (CMAKE_BUILD_TYPE MATCHES "stm32f103_bluepill" OR CMAKE_BUILD_TYPE MATCHES "Debug")
    #[[
        stm32f1 -> Creating bin/stm32/bluepill.elf
    arm-none-eabi-gcc -DRCC_LED1=RCC_GPIOC -DPORT_LED1=GPIOC -DPIN_LED1=GPIO13  --static -nostartfiles -std=c11 -g3 -Os -fno-common -ffunction-sections -fdata-sections -I./libopencm3/include -L./libopencm3/lib -mcpu=cortex-m3 -mthumb -msoft-float -DSTM32F1 -DLITTLE_BIT=200000 -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group template_stm32.c -T ld.stm32.basic -lopencm3_stm32f1 -o bin/stm32/bluepill.elf
    ]]

    set(STM32_DEVICE STM32F103C8T6)
    set(LIBOPENCM3_BUILD_TARGET stm32/f1)
    set(LIBOPENCM3_LIB_TARGET opencm3_stm32f1)
    set(PLATFORM_ARCH STM32F1)

    set(STM32_DEFINES "-DSTM32F1")
    set(STM32_C_FLAGS "-mcpu=cortex-m3 -mthumb -msoft-float -mfix-cortex-m3-ldrd")
    set(STM32_CXX_FLAGS "-mcpu=cortex-m3 -mthumb -msoft-float -mfix-cortex-m3-ldrd")

    set(STM32_LIBS "-l${LIBOPENCM3_LIB_TARGET}")
#    set(STM32_LINKER_FLAGS "-T${LIBOPENCM3_DIR}/lib/stm32/f1/stm32f103x8.ld")
    set(STM32_LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/ld/stm32/stm32f103c8t6.ld")
    #    set(STM32_LINKER_FLAGS "-T ${CMAKE_SOURCE_DIR}/stm32f103c8t6.ld")

elseif (CMAKE_BUILD_TYPE MATCHES "stm32f4_black")
    #[[
        stm32f4 -> Creating bin/stm32/black-stm32f407ve-v2.0.elf
    arm-none-eabi-gcc -DRCC_LED1=RCC_GPIOA -DPORT_LED1=GPIOA -DPIN_LED1=GPIO6  --static -nostartfiles -std=c11 -g3 -Os -fno-common -ffunction-sections -fdata-sections -I./libopencm3/include -L./libopencm3/lib -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DSTM32F4 -DLITTLE_BIT=800000 -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group template_stm32.c -T ld.stm32.basic -lopencm3_stm32f4 -o bin/stm32/black-stm32f407ve-v2.0.elf
    ]]

    set(STM32_DEVICE STM32F407VET6)
    set(LIBOPENCM3_BUILD_TARGET stm32/f4)
    set(LIBOPENCM3_LIB_TARGET opencm3_stm32f4)
    set(PLATFORM_ARCH STM32F4)

    # Set STM32 SoC specific variables
    set(STM32_DEFINES "-DSTM32F4")
    set(STM32_C_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
    set(STM32_CXX_FLAGS "-mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")

    set(STM32_LIBS "-l${LIBOPENCM3_LIB_TARGET}")
    set(STM32_LINKER_FLAGS "-T${CMAKE_SOURCE_DIR}/ld/stm32/stm32f407vet6.ld")

endif ()

message(STATUS "Device : ${STM32_DEVICE}")
message(STATUS "PLATFORM_ARCH : ${PLATFORM_ARCH}")
message(STATUS "DEFINES : ${STM32_DEFINES}")
message(STATUS "C FLAGS : ${STM32_C_FLAGS}")
message(STATUS "CXX FLAGS : ${STM32_CXX_FLAGS}")
message(STATUS "LIBS : ${STM32_LIBS}")
message(STATUS "LINKER FLAGS : ${STM32_LINKER_FLAGS}")

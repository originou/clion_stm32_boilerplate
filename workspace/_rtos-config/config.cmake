# FreeRTOS configuration
if (STM32_DEVICE MATCHES "STM32F103C8T6")
    add_definitions(-DSTM32_CONFIG_CLOCK_HZ=72000000)
elseif (STM32_DEVICE MATCHES "STM32F407VET6")
    add_definitions(-DSTM32_CONFIG_CLOCK_HZ=72000000)
endif ()

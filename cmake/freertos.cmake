# define different modules paths
set(FREERTOS_DIR ${CMAKE_SOURCE_DIR}/rtos/FreeRTOS/Source)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS "${FREERTOS_DIR}")
    message(FATAL_ERROR "FreeRTOS not found.")
endif()

message("-----------FREERTOS CONFIGURATION------------")
message(STATUS "FreeRTOS dir set to: ${FREERTOS_DIR}")

cmake_minimum_required(VERSION 3.12)

set(FREERTOS_INC_DIR
        ${CONFIG_DIR}/incl-template #FreeRTOSConfig.h
        ${FREERTOS_DIR}/include
        ${FREERTOS_DIR}/portable/GCC/ARM_CM3
        )
#include_directories(${FREERTOS_INC_DIR})

set(FREERTOS_LIB_SRC
        ${FREERTOS_DIR}/portable/GCC/ARM_CM3/port.c
        ${FREERTOS_DIR}/portable/MemMang/heap_4.c
        ${FREERTOS_DIR}/list.c
        ${FREERTOS_DIR}/tasks.c
        ${FREERTOS_DIR}/queue.c
        )

set(SOURCES src/main.c)


set(FREERTOS_INC_DIR ${FREERTOS_INC_DIR} PARENT_SCOPE)
set(FREERTOS_LIB_SRC ${FREERTOS_LIB_SRC} PARENT_SCOPE)
set(SOURCES ${SOURCES} PARENT_SCOPE)
set(APPLICATION_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

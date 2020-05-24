cmake_minimum_required(VERSION 3.12)

#set(APPLICATION_NAME miniblink)

#message("-----------${APPLICATION_NAME} Project Information------------")

#set_source_files_properties(C_SOURCES PROPRTIES LANGUAGE C)
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
        )

#add_library(freertos STATIC ${FREERTOS_LIB_SRC})

#set_target_properties(freertos PROPERTIES LINKER_LANGUAGE C C_STANDARD ${CMAKE_C_STANDARD})

#set(EXTERNAL_LIBS ${EXTERNAL_LIBS} freertos)

set(SOURCES
        src/main.c
        src/tasks/blink.c
        src/tasks/blink.h
        )
#message("CURRENT DIR : ${CMAKE_CURRENT_SOURCE_DIR}")
#set(SOURCES ${SOURCES} PARENT_SCOPE)

#set(ELF_FILE ${APPLICATION_NAME}.elf PARENT_SCOPE)
#set(BIN_FILE ${APPLICATION_NAME}.bin)
#set(HEX_FILE ${APPLICATION_NAME}.hex)

#add_executable(${ELF_FILE} ${SOURCES} PARENT_SCOPE)
#target_link_libraries(${ELF_FILE} ${LIBOPENCM3_LIB_TARGET} freertos PARENT_SCOPE)
#
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Map=${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.map")
#set(HEX_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.hex)
#set(BIN_FILE ${PROJECT_SOURCE_DIR}/build/${PROJECT_NAME}.bin)

#message(STATUS "DEFAULT OBJCOPY: ${OBJCOPY}")
#add_custom_command(TARGET ${ELF_FILE} POST_BUILD
#        COMMAND ${OBJCOPY} -Oihex $<TARGET_FILE:${ELF_FILE}> ${HEX_FILE}
#        COMMAND ${OBJCOPY} -Obinary $<TARGET_FILE:${ELF_FILE}> ${BIN_FILE}
#        COMMENT "Building ${HEX_FILE} \nBuilding ${BIN_FILE}")

set(FREERTOS_INC_DIR ${FREERTOS_INC_DIR} PARENT_SCOPE)
set(FREERTOS_LIB_SRC ${FREERTOS_LIB_SRC} PARENT_SCOPE)
set(SOURCES ${SOURCES} PARENT_SCOPE)
set(APPLICATION_CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

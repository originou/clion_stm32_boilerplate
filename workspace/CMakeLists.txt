cmake_minimum_required(VERSION 3.12)

#include_directories(config/)
set(CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/_rtos-config)
#include(_rtos-config/config.cmake)

set(LIST_APPLICATION miniblink uart)

message("-----------Workspace Information------------")
message(STATUS "List of application: ${LIST_APPLICATION}")
#add_subdirectory(${LIST_PROJECTS})

foreach (APPLICATION_NAME ${LIST_APPLICATION})
    message("-----------${APPLICATION_NAME} Project Information------------")

    set(ELF_FILE ${APPLICATION_NAME}.elf)
    set(BIN_FILE ${APPLICATION_NAME}.bin)
    set(HEX_FILE ${APPLICATION_NAME}.hex)


    add_subdirectory(${APPLICATION_NAME})



    list(TRANSFORM SOURCES PREPEND "${APPLICATION_CURRENT_DIR}/" )

    message(STATUS "FREERTOS INCLUDE DIR: ${FREERTOS_INC_DIR}")
    message(STATUS "FREERTOS SOURCES: ${FREERTOS_LIB_SRC}")
    message(STATUS "Project SOURCES: ${SOURCES}")

    include_directories(${FREERTOS_INC_DIR})
    add_library(freertos-${APPLICATION_NAME} STATIC ${FREERTOS_LIB_SRC})

    set_target_properties(freertos-${APPLICATION_NAME} PROPERTIES LINKER_LANGUAGE C C_STANDARD ${CMAKE_C_STANDARD})

    set(EXTERNAL_LIBS ${EXTERNAL_LIBS} freertos-${APPLICATION_NAME})

    add_executable(${ELF_FILE} ${SOURCES})
    target_link_libraries(${ELF_FILE} ${LIBOPENCM3_LIB_TARGET} freertos-${APPLICATION_NAME})

    add_custom_command(TARGET ${ELF_FILE} POST_BUILD
            COMMAND ${OBJCOPY} -Oihex $<TARGET_FILE:${ELF_FILE}> ${OUTPUT_DIR}/${HEX_FILE}
            COMMAND ${OBJCOPY} -Obinary $<TARGET_FILE:${ELF_FILE}> ${OUTPUT_DIR}/${BIN_FILE}
            COMMENT "Building ${OUTPUT_DIR}/${HEX_FILE} \nBuilding ${OUTPUT_DIR}/${BIN_FILE}")
endforeach ()

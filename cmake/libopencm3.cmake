set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)

# Make sure that git submodule is initialized and updated
if (NOT EXISTS ${LIBOPENCM3_DIR}/Makefile)
    message(FATAL_ERROR "libopencm3 submodule not found. Initialize with 'git submodule update --init' in the source directory")
endif ()

set(LIBOPENCM3_DIR ${CMAKE_SOURCE_DIR}/libopencm3)
link_directories(${LIBOPENCM3_DIR}/lib)

include_directories(${LIBOPENCM3_DIR}/include)

message("-----------LIBOPENCM3 CONFIGURATION------------")
message(STATUS "Libopemc3 dir set to: ${LIBOPENCM3_DIR}")

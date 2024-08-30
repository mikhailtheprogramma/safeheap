cmake_minimum_required(VERSION 3.10)
project(SafeHeap)

# Set the output directory for libraries
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# Include header files
include_directories("include")

# Find all source files
file(GLOB SOURCES "src/*.c")

# Compile each source file into a shared library (.so)
foreach(SOURCE_FILE ${SOURCES})
    get_filename_component(LIB_NAME ${SOURCE_FILE} NAME_WE)
    add_library(${LIB_NAME} SHARED ${SOURCE_FILE})
endforeach()
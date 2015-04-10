cmake_minimum_required(VERSION 2.8.8)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules" ${CMAKE_MODULE_PATH})

project(HuffmanAlgorythm)

if(NOT WIN32)
    string(ASCII 27 Esc)
    set(BOLD_RED "${Esc}[1;31m")
    set(BOLD_BLUE "${Esc}[1;34m")
    set(RESET_COLOR "${Esc}[m")
endif()

######################
# Check requirements
######################

set(REQ_ERR_COUNTER 0)

find_package(PkgConfig REQUIRED)
if(NOT PKG_CONFIG_FOUND)
    message(FATAL_ERROR "${BOLD_BLUE}Pkg-confing not found${RESET_COLOR}")
endif()

######################
#       General
######################

set (CMAKE_CXX_FLAGS "-Wall -pedantic-errors -g -std=c++11") 

set(TARGET_NAME "bin")
set(TARGET ${TARGET_NAME})
set(SRC_DIR "src/")

set (CMAKE_C_FLAGS "-Wall")

file(GLOB_RECURSE SRC_NAMES ${SRC_DIR}*.cpp)
add_executable(${TARGET} ${SRC_NAMES})

######################
# Include Settings
######################

include_directories(
    ${PROJECT_BINARY_DIR}
    ${SRC_DIR}
)

target_link_libraries(
    ${TARGET}
)

##################
# Install target
##################

install(TARGETS ${TARGET} DESTINATION ${TARGET_NAME})


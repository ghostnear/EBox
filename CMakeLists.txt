cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_compile_definitions(BUILD_TYPE_${CMAKE_BUILD_TYPE})

project(EBox)

file(
GLOB_RECURSE
SOURCES
    src/*.c
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCES}
)

target_include_directories(
    ${PROJECT_NAME}
PRIVATE
    ./include
)
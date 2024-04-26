cmake_minimum_required(VERSION 3.5)

include("cmake/config.cmake")

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

target_compile_options(
    ${PROJECT_NAME}
PRIVATE
    -Wall
    -Wextra
    -Werror
    -Wno-unused-parameter
    -Wno-unused-variable
    -Wno-unused-function
)

include("cmake/libraries.cmake")

include("cmake/post.cmake")
cmake_minimum_required(VERSION 3.5)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
add_compile_definitions(BUILD_TYPE_${CMAKE_BUILD_TYPE})
add_compile_definitions(BUILD_PLATFORM_${CMAKE_BUILD_PLATFORM})

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

set(OpenGL_GL_PREFERENCE "GLVND")

find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(
	${PROJECT_NAME}
	PUBLIC
		GLEW::GLEW
		OpenGL::GL glm::glm
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
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
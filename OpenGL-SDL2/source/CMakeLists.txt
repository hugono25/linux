cmake_minimum_required(VERSION 3.20)

project(gl VERSION 1.0.0)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(glBinary src/main.c
src/glad.c
src/Window.c
src/lAlgebra.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(glBinary PRIVATE SDL2
cglm)

add_subdirectory(external/cglm/)

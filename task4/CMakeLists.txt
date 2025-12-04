cmake_minimum_required(VERSION 3.10)
project(task4 C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

# 👇 Это важно для отладки
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Добавляем -g и -O0 в Debug
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g -O0)
endif()

add_executable(${CMAKE_PROJECT_NAME} main.c foo.c)
add_executable(${CMAKE_PROJECT_NAME}2 main2.c foo.c)
target_link_libraries(${CMAKE_PROJECT_NAME} m)
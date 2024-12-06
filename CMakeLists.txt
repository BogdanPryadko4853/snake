cmake_minimum_required(VERSION 3.29)
project(snake C)

set(CMAKE_C_STANDARD 11)

# Добавляем библиотеку raylib
include(FetchContent)

FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        master
)

FetchContent_MakeAvailable(raylib)

add_executable(snake main.c
"main.c"
snake.c
snake.h)

target_link_libraries(snake raylib)
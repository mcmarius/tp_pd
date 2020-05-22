cmake_minimum_required(VERSION 3.5)
project(tp C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -pedantic")
add_executable(tp main.c)
target_link_libraries(tp m)

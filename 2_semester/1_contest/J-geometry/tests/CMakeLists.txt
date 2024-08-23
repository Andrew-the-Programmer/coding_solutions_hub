project(oop-assignments)

cmake_minimum_required(VERSION 3.16)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces")
set(CMAKE_EXPORT_COMPILE_COMMANDS  ON)

file(GLOB SRC src/*.cpp)

add_executable(geometry_public_test geometry_main.cpp ${SRC})

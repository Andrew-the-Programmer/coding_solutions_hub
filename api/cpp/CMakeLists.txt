cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces"
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED PROJECT_NAME)
  set(PROJECT_NAME solution)
endif()
if(NOT DEFINED PROJECT_DIR)
  set(PROJECT_DIR ${PROJECT_NAME})
endif()

project(${PROJECT_NAME})

include_directories(.)
file(GLOB_RECURSE SRC ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})

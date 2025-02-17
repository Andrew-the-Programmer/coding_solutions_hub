cmake_minimum_required(VERSION 3.22.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -Wall -Wextra -pedantic -Werror -Wno-self-assign-overloaded -Wno-missing-braces"
)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT DEFINED SOLUTION_NAME)
  set(SOLUTION_NAME solution)
endif()
if(NOT DEFINED SOLUTION_DIR)
  set(SOLUTION_DIR ${SOLUTION_NAME})
endif()

project(${SOLUTION_NAME})

message(STATUS "Solution name: ${SOLUTION_NAME}")
message(STATUS "Solution dir: ${SOLUTION_DIR}")

include_directories(.)
file(GLOB_RECURSE SRC ${SOLUTION_DIR}/*.cpp)

add_executable(${SOLUTION_NAME} ${SRC})

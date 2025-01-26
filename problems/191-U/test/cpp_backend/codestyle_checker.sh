#!/bin/bash

cd "$(dirname "$0")" || exit

SOLUTION_DIRECTORY=./solution

./run-clang-format.py -r "$SOLUTION_DIRECTORY" &&
clang-tidy -extra-arg=-std=c++20 -p ./build "$SOLUTION_DIRECTORY"/**/*.cpp

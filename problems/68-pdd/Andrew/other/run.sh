#!/bin/bash

cd "$(dirname "$0")" || exit
cd .. || exit

build_dir=./out/build
project_name=Solution

"$build_dir/$project_name" "$*"

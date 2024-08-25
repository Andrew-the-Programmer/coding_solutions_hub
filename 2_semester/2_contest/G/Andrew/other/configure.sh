#!/bin/bash

cd "$(dirname "$0")" || exit

source_dir=".."
build_dir="$source_dir/out/build"

mkdir -p "$build_dir"
cmake -S "$source_dir" -B "$build_dir"

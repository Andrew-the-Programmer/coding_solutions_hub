#!/bin/bash

cd "$(dirname "$0")" || exit

build_dir="../out/build"

cd "$build_dir" && make

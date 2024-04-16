#!/bin/bash

echo "Copy"

solution_name="solution.zip"
dest_dir="$HOME/MEGA/programming/VS_code/mipt/algorithms/hw/cpp_psami_base_2023/geometry"
dest_file="$dest_dir/$solution_name"

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR" || exit

"./zip_files.sh"

cp solution.zip "$dest_dir"

cd "$dest_dir" || exit

unzip -o "$dest_file"

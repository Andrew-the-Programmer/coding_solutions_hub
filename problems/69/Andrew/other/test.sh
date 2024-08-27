#!/bin/bash

cd "$(dirname "$0")" || exit

exe="./run.sh"
input_file_name="input.txt"
output_file_name="output.txt"
tests_dir=../../test
tests_db_dir="$tests_dir/tests"
confirm_cmd="$tests_dir/confirm.py"

function ldir() {
    cd "$1" || exit 1
	find . -mindepth 1 -maxdepth 1 -type d \( ! -iname ".*" \) | sed 's|^\./||g'
}

for test_name in $(ldir "$tests_db_dir"); do
    test_dir="$tests_db_dir/$test_name"
    output_file="$test_dir/$output_file_name"
    input_file="$test_dir/$input_file_name"
    < "$input_file" "$exe" > "$output_file"
    "$confirm_cmd" --test_name "$test_name"
done

#!/bin/bash

cpp_psami_base_2023_dir="$HOME/MEGA/mipt/courses/c++/cpp-hw/cpp_psami_base_2023"
problem_name="iterops"

#----------------------------------------------------------------

if [ -z "$problem_name" ]; then
	echo "problem_name not set"
	exit 1
fi

test_dir="$cpp_psami_base_2023_dir/$problem_name"

SCRIPT_DIR=$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &>/dev/null && pwd)
cd "$SCRIPT_DIR" || exit

if ! "$PWD/zip_files.sh"; then
	echo "could not create zip file or everything is up to date"
	# exit 1
fi

zip_file_name="solution.zip"

unzip -o "$PWD/$zip_file_name" -d "$test_dir"

exit 0

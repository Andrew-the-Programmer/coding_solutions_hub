#!/bin/bash

# NOTE: Make sure to specify problem_name
problem_name=""

src_dir="../solution"

# NOTE: Make sure to specify your own target directory
target_dir="$HOME/MEGA/mipt/courses/algorithms/algorithms_hw/cpp_psami_base_2023/$problem_name"

function Init() {
	if ! problem_name; then
		echo "problem_name not set"
		exit 1
	fi
	cd "$(dirname "$0")" || exit
}

function Exit() {
	exit $?
}

function Export() {
	mkdir -p "$target_dir"

	cd .. || exit

	cmd="stow"

	args=(
		"-t"
		"$target_dir"
		"--dotfiles"
        "-d"
		"$src_dir"
        "."
	)

	eval "${cmd} ${args[*]}"

	return $?
}

Init
Export
Exit

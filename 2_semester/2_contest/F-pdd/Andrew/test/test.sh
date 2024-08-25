#!/bin/bash

cd "$(dirname "$0")" || exit

exe="./run.sh"
inputfile="input.txt"
outputfile="output.txt"
tests_dir="../../test/tests"

for d in "${tests_dir/*[@]}"; do
    < "$d/$inputfile" "$exe" > "$d/$outputfile"
    ./confirm.py "$d"
done

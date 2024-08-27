#!/bin/bash

echo "Zip"

problem_dir=".."
zip_file="solution.zip"

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
cd "$SCRIPT_DIR" || exit

exclude=(
  "*etc*"
  "*build*"
  "*ignore*"
  "*other*"
  "*out*"
)
cmd="zip"
args=(
  "-uv"
  "$zip_file"
  "-r"
  "$problem_dir"
)

for e in "${exclude[@]}"
do
  args+=("--exclude=$e")
done

eval "${cmd} ${args[*]}"

exit $?

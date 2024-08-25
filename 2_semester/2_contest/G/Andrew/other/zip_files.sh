#!/bin/bash

echo "Zip"

cd "$(dirname "$0")" || exit

zip_file="solution.zip"
solution_dir="../solution"

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

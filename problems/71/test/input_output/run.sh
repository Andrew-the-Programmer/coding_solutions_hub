#!/usr/bin/env bash

exe=$1
input=$2
output=$3

"$exe" < "$input" > "$output"

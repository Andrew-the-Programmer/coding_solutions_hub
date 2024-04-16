#!/bin/bash

echo "Zip"

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )

cd "$SCRIPT_DIR" || exit

# tar -uvf solution.zip --exclude="*etc*" --exclude="*build*" ../

zip -u solution.zip --exclude="*etc*" --exclude="*build*" -r ".."

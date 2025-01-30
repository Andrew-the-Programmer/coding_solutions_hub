#!/usr/bin/env python3

import subprocess

from constants import SOLUTION_DIR, ZIP_FILE


def CreateZipFile() -> subprocess.CompletedProcess:
    print(ZIP_FILE, SOLUTION_DIR)
    return subprocess.run(["zip", "-r", ZIP_FILE, SOLUTION_DIR])


def main() -> None:
    CreateZipFile().check_returncode()


if __name__ == "__main__":
    main()

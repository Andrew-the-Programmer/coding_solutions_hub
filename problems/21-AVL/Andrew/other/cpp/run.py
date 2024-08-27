#!/usr/bin/env python3

import subprocess

from constants import SOLUTION_EXECUTABLE


def Run() -> subprocess.CompletedProcess:
    return subprocess.run(SOLUTION_EXECUTABLE)


def main() -> None:
    Run().check_returncode()


if __name__ == "__main__":
    main()

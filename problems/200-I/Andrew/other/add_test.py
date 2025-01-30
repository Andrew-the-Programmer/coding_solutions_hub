#!/bin/python3

import subprocess

from constants import ADD_TEST_EXECUTABLE


def AddTest() -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            ADD_TEST_EXECUTABLE,
        ],
        check=False,
    )


def main() -> None:
    AddTest().check_returncode()


if __name__ == "__main__":
    main()

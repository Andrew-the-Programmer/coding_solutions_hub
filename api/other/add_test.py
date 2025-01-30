#!/bin/python3

import argparse
import subprocess

from constants import ADD_TEST_EXECUTABLE


def AddTest(args: list[str]) -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            ADD_TEST_EXECUTABLE,
        ]
        + list(args),
        check=False,
    )


def main() -> None:
    parser = argparse.ArgumentParser(description="Test all cases")
    _, args = parser.parse_known_args()
    AddTest(args)


if __name__ == "__main__":
    main()

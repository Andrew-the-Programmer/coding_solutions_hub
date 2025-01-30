#!/bin/python3

import argparse
import pathlib
import subprocess

from constants import SolutionExecutable, TEST_EXECUTABLE


def Test(solution_dir: pathlib.Path) -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            TEST_EXECUTABLE,
            "-e",
            SolutionExecutable(solution_dir),
            "-s",
            solution_dir,
        ],
        check=False,
    )


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pathlib.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    Test(solution_dir)


if __name__ == "__main__":
    main()

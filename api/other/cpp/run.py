#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

from constants import SolutionExecutable


def Run(solution_dir: pl.Path) -> subprocess.CompletedProcess:
    solution_executable = SolutionExecutable(solution_dir)
    return subprocess.run([solution_executable], check=False)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pl.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    Run(solution_dir)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

from constants import BuildDir, CMakeArgs, SolutionExecutable


def Build(solution_dir: pl.Path) -> subprocess.CompletedProcess:
    build_dir = BuildDir(solution_dir)
    build_dir.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            "cmake",
            "-B",
            build_dir,
        ]
        + CMakeArgs(solution_dir),
        check=True,
    )
    return subprocess.run(["make", "-C", build_dir], check=False)


def Run(solution_dir: pl.Path) -> subprocess.CompletedProcess:
    solution_executable = SolutionExecutable(solution_dir)
    return subprocess.run([solution_executable], check=False)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pl.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    Build(solution_dir).check_returncode()
    Run(solution_dir)


if __name__ == "__main__":
    main()

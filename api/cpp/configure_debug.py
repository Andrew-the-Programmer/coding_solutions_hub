#!/usr/bin/env python3

import argparse
import pathlib
import subprocess

from constants import CMakeArgs, DebugDir


def ConfigureDebug(solution_dir: pathlib.Path) -> subprocess.CompletedProcess:
    cmake_dir = DebugDir(solution_dir)
    cmake_dir.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            "cmake",
            "-DCMAKE_BUILD_TYPE=Debug",
            "-B",
            cmake_dir,
        ]
        + CMakeArgs(solution_dir),
        check=True,
    )
    return subprocess.run(["make", "-C", cmake_dir], check=False)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pathlib.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    ConfigureDebug(solution_dir)


if __name__ == "__main__":
    main()

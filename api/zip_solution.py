#!/usr/bin/env python3

import argparse
import pathlib
import subprocess


def ProjectName(solution_dir: pathlib.Path) -> str:
    return solution_dir.name


def UserDir(solution_dir: pathlib.Path) -> pathlib.Path:
    return solution_dir.parent


def ZipFile(solution_dir: pathlib.Path) -> pathlib.Path:
    return UserDir(solution_dir) / f"{ProjectName(solution_dir)}.zip"


def CreateZipFile(solution_dir: pathlib.Path) -> subprocess.CompletedProcess:
    return subprocess.run(
        ["zip", "-r", ZipFile(solution_dir), solution_dir], check=False
    )


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pathlib.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    CreateZipFile(solution_dir)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import argparse
import pathlib
import subprocess

from project_navigator import SolutionNavigator


def ZipFile(solution_dir: pathlib.Path) -> pathlib.Path:
    sn = SolutionNavigator(solution_dir)
    return sn.Hero() / f"{sn.Name()}.zip"


def ZipSolution(solution_dir: pathlib.Path):
    return subprocess.run(
        ["zip", "-r", ZipFile(solution_dir), solution_dir], check=False
    )


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pathlib.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    ZipSolution(solution_dir)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import argparse
import pathlib
import subprocess

from constants import DebugExecutable, ProjectName


def Debug(solution_dir: pathlib.Path) -> subprocess.CompletedProcess:
    project_name = ProjectName(solution_dir)
    debug_executable = DebugExecutable(project_name)
    return subprocess.run(["gdb", "-tui", debug_executable], check=False)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("solution_dir", type=pathlib.Path, default=None)
    args = parser.parse_args()
    solution_dir = args.solution_dir
    Debug(solution_dir)


if __name__ == "__main__":
    main()

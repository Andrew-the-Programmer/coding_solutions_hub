#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

from check import Check
from constants import CasesDir, ListCases
from run import RunTest


def TestCaseBeginMsg(case_name: str) -> None:
    print(f"=== {case_name} ===")


def TestCase(case_path: pl.Path, executable: pl.Path) -> subprocess.CompletedProcess:
    TestCaseBeginMsg(case_name=case_path.name)
    e = RunTest(case_path=case_path, executable=executable)
    if e.returncode == 0:
        Check(case_path=case_path)
    return e


def Test(executable: pl.Path) -> None:
    for case_path in ListCases():
        TestCase(case_path, executable)


def main():
    parser = argparse.ArgumentParser(description="Test all cases")
    parser.add_argument(
        "--executable",
        "-e",
        required=True,
        type=pl.Path,
    )
    parser.add_argument(
        "--solution-dir",
        "-s",
        required=True,
        type=pl.Path,
    )
    args, _ = parser.parse_known_args()
    executable: pl.Path = args.executable
    solution_dir: pl.Path = args.solution_dir
    CASES_DIR = CasesDir(solution_dir)
    Test(executable)


if __name__ == "__main__":
    main()

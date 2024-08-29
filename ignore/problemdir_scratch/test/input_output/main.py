#!/usr/bin/env python3

import argparse
import os
import pathlib as pl
import subprocess

import sys
from input_output.check import Check
from input_output.constants import CASES_DIR, GetCasePath, ListCases
from input_output.run import RunTest




def TestCaseBeginMsg(case_name: str) -> None:
    print(f"=== {case_name} ===")


def TestCase(case_path: pl.Path, executable: pl.Path) -> subprocess.CompletedProcess:
    TestCaseBeginMsg(case_name=case_path.name)
    e = RunTest(case_path=case_path, executable=executable)
    if e.returncode == 0:
        Check(case_path=case_path)
    return e


def Test(executable: pl.Path) -> None:
    if (
        executable is None
        or not executable.is_file()
        or not os.access(executable, os.X_OK)
    ):
        print(f"Executable '{executable}' don't exist or is not executable")
        sys.exit(1)
    for case_path in ListCases():
        TestCase(case_path, executable)


def main():
    parser = argparse.ArgumentParser(description="Test all cases")
    parser.add_argument(
        "--executable", "-e", type=pl.Path, help="Path to the executable", default=None
    )
    args: argparse.Namespace = parser.parse_args()

    executable: pl.Path | None = args.executable

    if executable is None:
        print("Executable not specified")
        sys.exit(1)

    Test(executable)


if __name__ == "__main__":
    main()

#!/usr/bin/env python3

import argparse
import os
import pathlib as pl
import subprocess
from typing import Any, TextIO

from .check import Check
from .run import RunTest


def Here() -> pl.Path:
    return pl.Path(__file__).parent


CASES_DIR = Here() / "cases"


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def ListCases() -> list[pl.Path]:
    return [x for x in CASES_DIR.iterdir() if x.is_dir()]


def TestCaseBeginMsg(case_name: str) -> None:
    print(f"=== {case_name} ===")


def TestCase(case_path: pl.Path, executable: pl.Path) -> Any:
    TestCaseBeginMsg(case_name=case_path.name)
    e = RunTest(case_path=case_path, executable=executable)
    if e.returncode == 0:
        Check(case_path=case_path)
    return e


def Test(executable: pl.Path) -> None:
    if not executable.is_file() or not os.access(executable, os.X_OK):
        print(f"Executable '{executable}' don't exist or is not executable")
        exit(1)
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
        exit(1)

    Test(executable)


if __name__ == "__main__":
    main()

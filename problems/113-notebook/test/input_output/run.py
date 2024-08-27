#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess
from typing import Any, TextIO


def Here() -> pl.Path:
    return pl.Path(__file__).parent


CASES_DIR = Here() / "cases"
OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def Run(
    *, executable: pl.Path, input_file: pl.Path, output_file: pl.Path
) -> subprocess.CompletedProcess:
    with input_file.open("r") as stdin, output_file.open("w") as stdout:
        return subprocess.run(executable, stdin=stdin, stdout=stdout)


def RunTest(*, case_path: pl.Path, executable: pl.Path) -> subprocess.CompletedProcess:
    input_file = GetInputFilePath(case_path)
    output_file = GetOutputFilePath(case_path)
    e = Run(executable=executable, input_file=input_file, output_file=output_file)
    # print(f"{e.stdout=}")
    if e.returncode != 0:
        print(f"Failed to run test {case_path.name}")
    return e


def main():
    parser = argparse.ArgumentParser(description="Check if test was passed")
    parser.add_argument(
        "--executable", type=pl.Path, help="Path to the executable", default=None
    )
    parser.add_argument(
        "--case-dir",
        type=pl.Path,
        help="Path to the output dir of the test",
        default=None,
    )
    parser.add_argument("--case-name", type=str, help="Test name", default=None)

    args: argparse.Namespace = parser.parse_args()

    executable: pl.Path | None = args.executable
    case_dir: pl.Path | None = args.case_dir
    case_name: str | None = args.case_name

    if executable is None:
        print("Executable not specified")
        exit(1)

    if case_name is not None:
        case_dir = GetCasePath(case_name)

    if case_dir is None:
        print("Case directory not specified")
        exit(1)

    e = RunTest(case_path=case_dir, executable=executable)

    return e


if __name__ == "__main__":
    main()

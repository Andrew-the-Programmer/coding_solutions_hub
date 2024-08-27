#!/usr/bin/env python3

import argparse
import pathlib as pl
from typing import TextIO


def Here() -> pl.Path:
    return pl.Path(__file__).parent


CASES_DIR = Here() / "cases"
print(f"{CASES_DIR=}")
OUTPUT_FILE_NAME = "output.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetCorrectOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / CORRECT_OUTPUT_FILE_NAME


def GetWords(f: TextIO) -> list[str]:
    return f.read().split()


def CompareOutputs(output1: TextIO, output2: TextIO) -> bool:
    return GetWords(output1) == GetWords(output2)


def Compare(f1: pl.Path, f2: pl.Path) -> bool:
    with open(f1, "r") as output1, open(f2, "r") as output2:
        return CompareOutputs(output1, output2)


def Check(case_path: pl.Path) -> bool:
    e = Compare(GetOutputFilePath(case_path),
                GetCorrectOutputFilePath(case_path))
    if not e:
        print(f"Test {case_path.name} failed")
    return e


def main():
    parser = argparse.ArgumentParser(description="Check if test was passed")
    parser.add_argument(
        "--case-dir", type=pl.Path, help="Path to the output dir of the test", default=None
    )
    parser.add_argument("--case-name", type=str,
                        help="Test name", default=None)

    args: argparse.Namespace = parser.parse_args()

    case_dir: pl.Path | None = args.case_dir
    case_name: str | None = args.case_name

    if case_name is not None:
        case_dir = GetCasePath(case_name)

    if case_dir is None:
        print("Test directory not specified")
        exit(1)

    case_name = case_dir.name

    Check(case_dir)


if __name__ == "__main__":
    main()

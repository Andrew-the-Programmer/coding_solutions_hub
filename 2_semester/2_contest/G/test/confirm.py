#!/usr/bin/env python3

import argparse
import os
import pathlib as pl
import sys
from typing import TextIO


def GetWords(f: TextIO) -> list[str]:
    return f.read().split()


def CompareOutputs(output1: TextIO, output2: TextIO) -> bool:
    return GetWords(output1) == GetWords(output2)


def Compare(f1: pl.Path, f2: pl.Path) -> bool:
    with open(f1, "r") as output1, open(f2, "r") as output2:
        return CompareOutputs(output1, output2)


def Init():
    abspath = os.path.abspath(__file__)
    dname = os.path.dirname(abspath)
    os.chdir(dname)


def main():
    parser = argparse.ArgumentParser(description="Optional app description")
    _ = parser.add_argument(
        "--tests_db_dir",
        type=pl.Path,
        help="Path to all tests",
        default="./tests",
    )
    _ = parser.add_argument(
        "--test_dir", type=pl.Path, help="Test directory", default=None
    )
    _ = parser.add_argument("--test_name", type=str, help="Test name", default=None)

    args: argparse.Namespace = parser.parse_args()

    test_dir: pl.Path | None = args.test_dir
    tests_db_dir: pl.Path = args.tests_db_dir
    test_name: str | None = args.test_name

    if test_name is not None:
        test_dir = tests_db_dir / test_name

    if test_dir is None:
        print("Test directory not specified")
        exit(1)

    test_name = test_dir.name

    if not test_dir.is_dir():
        print(f"Test {test_name} doesn't exist")
        exit(1)

    finput = test_dir / "input.txt"
    foutput = test_dir / "output.txt"
    fcorrect = test_dir / "correct_output.txt"

    if not finput.is_file():
        print(f"Input file {finput} doesn't exist")
        exit(1)

    if not foutput.is_file():
        print(f"Output file {foutput} doesn't exist")
        exit(1)

    if not fcorrect.is_file():
        print(f"Result file {fcorrect} doesn't exist")
        exit(1)

    success = Compare(foutput, fcorrect)
    if not success:
        print(f"Test {test_name} failed")


if __name__ == "__main__":
    Init()
    main()

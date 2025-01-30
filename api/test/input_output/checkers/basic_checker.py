#!/usr/bin/env python3

import argparse
import pathlib as pl
import sys
from typing import TextIO


def GetWords(f: TextIO) -> list[str]:
    return f.read().split()


def CompareOutputs(output1: TextIO, output2: TextIO) -> bool:
    return GetWords(output1) == GetWords(output2)


def Compare(f1: pl.Path, f2: pl.Path) -> bool:
    with f1.open("r") as output1, f2.open("r") as output2:
        return CompareOutputs(output1, output2)


def main() -> None:
    parser = argparse.ArgumentParser(description="Check if test was passed")
    parser.add_argument(
        "--input", type=pl.Path, help="Optional path to the input file", default=None
    )
    parser.add_argument(
        "--output", type=pl.Path, help="Path to the output file", default=None
    )
    parser.add_argument(
        "--correct-output",
        type=pl.Path,
        help="Path to the correct output file",
        default=None,
    )

    args: argparse.Namespace = parser.parse_args()

    output: pl.Path | None = args.output
    correct_output: pl.Path | None = args.correct_output

    if output is None or not output.is_file():
        print("Output not specified or does not exist")
        sys.exit(1)

    if correct_output is None or not correct_output.is_file():
        print("Correct output not specified or does not exist")
        sys.exit(1)

    match: bool = Compare(output, correct_output)
    if not match:
        sys.exit(1)


if __name__ == "__main__":
    main()

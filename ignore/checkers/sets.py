#!/usr/bin/env python3

import argparse
import pathlib as pl
import sys
from typing import TextIO


def GetWords(f: TextIO) -> list[str]:
    return f.read().split()


def GetSets(words: list[str]) -> set[str]:
    n = int(words.pop(0))
    sets = set(frozenset())
    for _ in range(n):
        m = int(words.pop(0))
        subset = frozenset(words.pop(0) for _ in range(m))
        sets.add(subset)
    return sets


def CompareOutputs(output1: TextIO, output2: TextIO) -> bool:
    words1 = GetWords(output1)
    words2 = GetWords(output2)
    sets1 = GetSets(words1)
    sets2 = GetSets(words2)
    return sets1 == sets2


def Compare(f1: pl.Path, f2: pl.Path) -> bool:
    with f1.open("r") as output1, f2.open("r") as output2:
        return CompareOutputs(output1, output2)


def main() -> None:
    parser = argparse.ArgumentParser(description="Check if test was passed")
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

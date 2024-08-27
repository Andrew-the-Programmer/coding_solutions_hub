#!/usr/bin/env python3

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
    if len(sys.argv) != 2:
        print("Wrong number of arguments")
        print("Please enter test_id")
        exit(1)


def main():
    Init()

    test_dir: pl.Path = pl.Path(sys.argv[1])

    # print(f"Testing {test_name}")
    # print(f"Cwd: {pl.Path.cwd()}")

    # test_dir = pl.Path.cwd() / "tests" / test_name

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
    main()

#!/usr/bin/env python3

import pathlib as pl
import subprocess

from .navigator import TestNavigator


def Check(test_dir: pl.Path) -> bool:
    test = TestNavigator(test_dir)
    nav = test.Root()
    checker = nav.FindChecker()
    input_file = test.InputFile()
    output_file = test.OutputFile()
    correct_output_file = test.CorrectOutputFile()
    e = subprocess.run(
        [
            checker,
            "--input",
            input_file,
            "--output",
            output_file,
            "--correct-output",
            correct_output_file,
        ],
        check=False,
    )
    if e.returncode != 0:
        print(f"Test {test.Name()} failed")
    return e

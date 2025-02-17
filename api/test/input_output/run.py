#!/usr/bin/env python3

import pathlib as pl
import subprocess

from .navigator import TestNavigator


def Run(*, executable: pl.Path, input_file: pl.Path, output_file: pl.Path):
    with input_file.open("r") as stdin, output_file.open("w") as stdout:
        return subprocess.run([executable], stdin=stdin, stdout=stdout, shell=True)


def RunTest(*, test_dir: pl.Path, executable: pl.Path):
    test = TestNavigator(test_dir)
    input_file = test.InputFile()
    output_file = test.OutputFile()
    e = Run(executable=executable, input_file=input_file,
            output_file=output_file)
    if e.returncode != 0:
        print(f"Failed to run test {test_dir.name}")
    return e

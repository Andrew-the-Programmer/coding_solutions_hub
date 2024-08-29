#!/usr/bin/env python3

import pathlib as pl
import subprocess

from input_output.constants import INPUT_FILE_NAME, OUTPUT_FILE_NAME


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def Run(
    *, executable: pl.Path, input_file: pl.Path, output_file: pl.Path
) -> subprocess.CompletedProcess:
    with input_file.open("r") as stdin, output_file.open("w") as stdout:
        return subprocess.run([executable], stdin=stdin, stdout=stdout, check=False)


def RunTest(*, case_path: pl.Path, executable: pl.Path) -> subprocess.CompletedProcess:
    input_file = GetInputFilePath(case_path)
    output_file = GetOutputFilePath(case_path)
    e = Run(executable=executable, input_file=input_file,
            output_file=output_file)
    if e.returncode != 0:
        print(f"Failed to run test {case_path.name}")
    return e

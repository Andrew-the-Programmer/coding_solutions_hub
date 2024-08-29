#!/usr/bin/env python3

import pathlib as pl
import subprocess

from input_output.constants import (CHECKER, GetCorrectOutputFilePath,
                                    GetInputFilePath, GetOutputFilePath)


def Check(case_path: pl.Path) -> bool:
    input_path = GetInputFilePath(case_path)
    output_path = GetOutputFilePath(case_path)
    correct_output = GetCorrectOutputFilePath(case_path)
    e = subprocess.run(
        [
            CHECKER,
            "--input",
            input_path,
            "--output",
            output_path,
            "--correct-output",
            correct_output,
        ],
        check=False,
    )
    if e.returncode != 0:
        print(f"Test {case_path.name} failed")
    return e

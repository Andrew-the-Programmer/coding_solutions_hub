#!/usr/bin/env python3

import pathlib as pl
import subprocess

from input_output.constants import (CASES_DIR, CHECKER,
                                    CORRECT_OUTPUT_FILE_NAME, OUTPUT_FILE_NAME)


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetCorrectOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / CORRECT_OUTPUT_FILE_NAME


def Check(case_path: pl.Path) -> bool:
    e = subprocess.run(
        [
            CHECKER,
            "--output",
            GetOutputFilePath(case_path),
            "--correct-output",
            GetCorrectOutputFilePath(case_path),
        ],
        check=False,
    )
    if not e:
        print(f"Test {case_path.name} failed")
    return e

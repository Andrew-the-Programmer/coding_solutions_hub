#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

from .constants import CASES_DIR, INPUT_FILE_NAME, OUTPUT_FILE_NAME, Here


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def Run(
    *, executable: pl.Path, input_file: pl.Path, output_file: pl.Path
) -> subprocess.CompletedProcess:
    with input_file.open("r") as stdin, output_file.open("w") as stdout:
        return subprocess.run([executable], stdin=stdin, stdout=stdout)
    # return subprocess.run([Here() / "run.sh", executable, input_file, output_file])


def RunTest(*, case_path: pl.Path, executable: pl.Path) -> subprocess.CompletedProcess:
    input_file = GetInputFilePath(case_path)
    output_file = GetOutputFilePath(case_path)
    e = Run(executable=executable, input_file=input_file,
            output_file=output_file)
    if e.returncode != 0:
        print(f"Failed to run test {case_path.name}")
    return e


def main():
    parser = argparse.ArgumentParser(description="Check if test was passed")
    parser.add_argument(
        "--executable", type=pl.Path, help="Path to the executable", default=None
    )
    parser.add_argument(
        "--case-path",
        type=pl.Path,
        help="Path to the output dir of the test",
        default=None,
    )
    parser.add_argument("--case-name", type=str,
                        help="Test name", default=None)

    args: argparse.Namespace = parser.parse_args()

    executable: pl.Path | None = args.executable
    case_path: pl.Path | None = args.case_dir
    case_name: str | None = args.case_name

    if executable is None:
        print("Executable not specified")
        exit(1)

    if case_name is not None:
        case_path = GetCasePath(case_name)

    if case_path is None:
        print("Case directory not specified")
        exit(1)

    e = RunTest(case_path=case_path, executable=executable)
    return e


if __name__ == "__main__":
    main()

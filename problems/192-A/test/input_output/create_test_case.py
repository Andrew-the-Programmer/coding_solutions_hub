#!/usr/bin/env python3

import argparse
import pathlib as pl
import re
import shutil
import subprocess
import sys

from constants import (GetCasePath, GetCorrectOutputFilePath, GetInputFilePath,
                       GetOutputFilePath, IsExecutable, ListCases)


def WriteToFile(filepath: pl.Path, text: str) -> None:
    filepath.parent.mkdir(parents=True, exist_ok=True)
    with filepath.open("w") as f:
        f.write(text)


def CreateFiles(case_path: pl.Path) -> None:
    case_path.mkdir(parents=True, exist_ok=True)
    input_file = GetInputFilePath(case_path)
    output_file = GetOutputFilePath(case_path)
    correct_output_file = GetCorrectOutputFilePath(case_path)
    input_file.touch()
    output_file.touch()
    correct_output_file.touch()


def GenerateOutput(
    executable: pl.Path, input_file: pl.Path, output_file: pl.Path
) -> subprocess.CompletedProcess:
    with input_file.open("r") as stdin, output_file.open("w") as stdout:
        return subprocess.run([executable], stdin=stdin, stdout=stdout, check=False)


def GetUniqueCaseName() -> str:
    cases = ListCases()
    digit_cases = [int(x.name) for x in cases if re.match(r"[0-9]+", x.name)]
    return str(max(digit_cases) + 1) if digit_cases else "0"


def InputCaseName() -> None:
    msg = """
Input new test name
(or press enter to create a unique one)
>"""
    return input(msg) or GetUniqueCaseName()


def AskCasePath(case_path: pl.Path | None) -> pl.Path:
    return case_path if case_path is not None else GetCasePath(InputCaseName())


def InputText(msg: str) -> str:
    print(msg)
    lines = []
    while True:
        line = input()
        if line == "":
            break
        lines.append(line)
    return "\n".join(lines)


def GenerateTest(
    case_path: pl.Path | None, executable: pl.Path, ext_input_path: pl.Path
) -> None:
    case_path = AskCasePath(case_path)
    CreateFiles(case_path)
    input_file = GetInputFilePath(case_path)
    output_file = GetOutputFilePath(case_path)
    WriteToFile(input_file, ext_input_path.read_text())
    e = GenerateOutput(executable, input_file, output_file)
    if e.returncode != 0:
        print(f"Failed to generate test {case_path.name}, deleting ...")
        shutil.rmtree(case_path, ignore_errors=True)
        sys.exit(1)


def InputTest(
    case_path: pl.Path | None, input_text: str | None, output_text: str | None
) -> None:
    case_path = AskCasePath(case_path)
    if input_text is None:
        input_text = InputText("Input:")
    if output_text is None:
        output_text = InputText("Output:")
    CreateFiles(case_path)
    input_path = GetInputFilePath(case_path)
    output_path = GetOutputFilePath(case_path)
    correct_output_path = GetCorrectOutputFilePath(case_path)
    WriteToFile(input_path, input_text)
    WriteToFile(output_path, "")
    WriteToFile(correct_output_path, output_text)


def main() -> None:
    parser = argparse.ArgumentParser(description="Test all cases")
    parser.add_argument(
        "--case-path",
        type=pl.Path,
        help="Path to the test case",
        default=None,
    )
    parser.add_argument(
        "--executable",
        "-e",
        type=pl.Path,
        help="""\
Path to executable of the correct solution. \
If executable and input-file are specified, \
correct output will be genereted by executable with stdin as input-file""",
        default=None,
    )
    parser.add_argument(
        "--input-file",
        "-i",
        type=pl.Path,
        help="Path to the file with input",
        default=None,
    )
    parser.add_argument(
        "--output-file",
        "-o",
        type=pl.Path,
        help="Path to the file with correct output",
        default=None,
    )
    args: argparse.Namespace = parser.parse_args()

    case_path: pl.Path | None = args.case_path
    executable: pl.Path | None = args.executable
    input_file: pl.Path | None = args.input_file
    output_file: pl.Path | None = args.output_file

    if executable is not None:
        if output_file is not None:
            print("Executable specified with the output-file")
            sys.exit(1)
        if input_file is None:
            print("Executable specified without the input-file")
            sys.exit(1)
        if not IsExecutable(executable):
            print(
                f"Executable '{executable}' don't exist or is not executable")
            sys.exit(1)
        if not input_file.is_file():
            print(f"Input file '{input_file}' don't exist")
            sys.exit(1)
        GenerateTest(case_path, executable, input_file)
        sys.exit(0)

    input_text: str | None = None
    output_text: str | None = None
    if input_file is not None:
        input_text = input_file.read_text()
    if output_file is not None:
        output_text = output_file.read_text()
    if case_path is None:
        case_path = GetCasePath(GetUniqueCaseName())
    InputTest(case_path, input_text, output_text)


if __name__ == "__main__":
    main()

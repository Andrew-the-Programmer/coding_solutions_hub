#!/usr/bin/env python3

import argparse
import pathlib as pl
import re
import subprocess

from constants import (GetCasePath, GetCorrectOutputFilePath, GetInputFilePath,
                       GetOutputFilePath, ListCases)


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


def GetUniqueCaseName() -> str:
    cases = ListCases()
    digit_cases = [int(x.name) for x in cases if re.match(r"[0-9]+", x.name)]
    return str(max(digit_cases) + 1) if digit_cases else "0"


def AskCaseName() -> None:
    msg = """
Input new test name
(or press enter to create a unique one)
>"""
    return input(msg) or GetUniqueCaseName()


def InputText(msg: str = "") -> str:
    print(msg)
    lines = []
    while True:
        line = input()
        if line == "":
            break
        lines.append(line)
    return "\n".join(lines)


def AskInput() -> str:
    return InputText("Input:")


def AskOutput() -> str:
    return InputText("Output:")


def InputTest(
    case_path: pl.Path | None, input_text: str | None, output_text: str | None
) -> None:
    if case_path is None:
        case_name = AskCaseName()
        case_path = GetCasePath(case_name)
    if input_text is None:
        input_text = AskInput()
    if output_text is None:
        output_text = AskOutput()
    CreateFiles(case_path)
    input_path = GetInputFilePath(case_path)
    correct_output_path = GetCorrectOutputFilePath(case_path)
    WriteToFile(input_path, input_text)
    WriteToFile(correct_output_path, output_text)


def GetOutput(executable: pl.Path | str, input_str: str) -> str:
    e = subprocess.run(
        [executable],
        input=input_str,
        text=True,
        encoding="utf-8",
        capture_output=True,
        check=False,
    )
    if e.returncode != 0:
        raise ValueError("Failed to generate output")
    output_str = e.stdout
    return output_str


def main() -> None:
    parser = argparse.ArgumentParser(description="Test all cases")
    parser.add_argument(
        "--test_name",
        "-n",
        type=str,
        default=None,
    )
    parser.add_argument(
        "--executable",
        "-e",
        type=pl.Path,
        help="""\
Path to executable of the correct solution. \
Correct output will be genereted by executable""",
        default=None,
    )
    parser.add_argument(
        "--input-file",
        type=pl.Path,
        help="Path to the file with input",
        default=None,
    )
    parser.add_argument(
        "--output-file",
        type=pl.Path,
        help="Path to the file with correct output",
        default=None,
    )
    parser.add_argument(
        "--input",
        "-i",
        type=str,
        default=None,
    )
    parser.add_argument(
        "--output",
        "-o",
        type=str,
        default=None,
    )
    args: argparse.Namespace = parser.parse_args()

    case_name: str | None = args.test_name
    executable: pl.Path | None = args.executable
    input_str: str | None = args.input
    output_str: str | None = args.output
    input_file: pl.Path | None = args.input_file
    output_file: pl.Path | None = args.output_file

    if input_file is not None:
        if input_str is not None:
            raise ValueError("Can't use --input with --input-file")
        input_str = input_file.read_text()

    if output_file is not None:
        if output_str is not None:
            raise ValueError("Can't use --output with --output-file")
        output_str = output_file.read_text()

    if executable is not None:
        if output_str is not None:
            raise ValueError("Can't use --output with --executable")
        if input_str is None:
            input_str = AskInput()
        output_str = GetOutput(executable, input_str)

    case_path = None
    if case_name is None:
        case_name = GetUniqueCaseName()
        case_path = GetCasePath(case_name)

    InputTest(case_path, input_str, output_str)


if __name__ == "__main__":
    main()

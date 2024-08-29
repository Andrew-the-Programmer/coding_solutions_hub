#!/usr/bin/env python3

import pathlib as pl
import re

from constants import (GetCasePath, GetCorrectOutputFilePath, GetInputFilePath,
                       ListCases, GetOutputFilePath)


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


def InputText(msg: str) -> str:
    print(msg)
    lines = []
    while True:
        line = input()
        if line == "":
            break
        lines.append(line)
    return "\n".join(lines)


def WriteToFile(filepath: pl.Path, text: str) -> None:
    filepath.parent.mkdir(parents=True, exist_ok=True)
    with filepath.open("w") as f:
        f.write(text)


def InputTestCase() -> None:
    case_name = InputCaseName()
    case_path = GetCasePath(case_name)
    input_text = InputText("Input:")
    output_text = InputText("Output:")
    input_path = GetInputFilePath(case_path)
    output_path = GetOutputFilePath(case_path)
    correct_output_path = GetCorrectOutputFilePath(case_path)
    WriteToFile(input_path, input_text)
    WriteToFile(output_path, "")
    WriteToFile(correct_output_path, output_text)


def main() -> None:
    InputTestCase()


if __name__ == "__main__":
    main()

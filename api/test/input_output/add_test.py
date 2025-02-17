#!/usr/bin/env python3

import pathlib as pl
import subprocess

from project_navigator import FileNavigator

from .navigator import RootNavigator, TestNavigator


def WriteToFile(filepath: pl.Path, text: str) -> None:
    filepath.parent.mkdir(parents=True, exist_ok=True)
    with filepath.open("w") as f:
        f.write(text)


def AskCaseName(tests_dir: pl.Path) -> None:
    msg = """
Input new test name
(or press enter to create a unique one)
>"""
    tn = TestNavigator(tests_dir)
    rn = tn.Root()
    return input(msg) or rn.GetUniqueTestName()


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


def GetOutput(executable: pl.Path | str, input_str: str) -> str:
    e = subprocess.run(
        [executable],
        input=input_str,
        text=True,
        encoding="utf-8",
        capture_output=True,
        check=False,
        shell=True,
    )
    if e.returncode != 0:
        raise ValueError("Failed to generate output")
    return e.stdout


def AddTest(
    *,
    file: pl.Path = None,
    tests_dir: pl.Path = None,
    input_text: str = None,
    output_text: str = None,
    test_name: str = None,
    executable: pl.Path = None,
    input_file: pl.Path = None,
    output_file: pl.Path = None,
) -> None:
    if input_file is not None:
        if input_text is not None:
            raise ValueError("Can't use input with input_file")
        input_text = input_file.read_text()

    if output_file is not None:
        if output_text is not None:
            raise ValueError("Can't use output with output_file")
        output_text = output_file.read_text()

    # try to find good solution
    if executable is None and output_text is None:
        fn = FileNavigator(file)
        pn = fn.Problem()
        executable = pn.GoodSolutionRunner()

    # get output with executable
    if executable is not None:
        if output_text is not None:
            raise ValueError("Can't use output with executable")
        if input_text is None:
            input_text = AskInput()
        print("Generating output...")
        output_text = GetOutput(executable, input_text)

    if input_text is None:
        input_text = AskInput()
    if output_text is None:
        output_text = AskOutput()

    rn: RootNavigator = None
    if tests_dir is not None:
        rn = TestNavigator(tests_dir).Root()
    if file is not None:
        rn = RootNavigator.FindRoot(file)

    if test_name is None:
        test_name = rn.GetUniqueTestName()
    test = rn.GetTest(test_name)
    test.Create()

    input_file = test.InputFile()
    correct_output_file = test.CorrectOutputFile()

    WriteToFile(input_file, input_text)
    WriteToFile(correct_output_file, output_text)

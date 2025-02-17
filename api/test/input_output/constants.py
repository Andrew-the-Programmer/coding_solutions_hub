import pathlib as pl
import shutil

from my_os import ListSubDir
from project_navigator import ProjectNavigator, InputOutputTestsNavigator



OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"
io_navigator = InputOutputTestsNavigator()
CHECKER = (
    ProjectNavigator.TestDir()
    / "input_output"
    / "checkers"
    / "basic_checker.py"
)


def FindChecker() -> pl.Path:
    return CHECKER


def GetCasePath(tests_dir: pl.Path, case_name: str) -> pl.Path:
    return tests_dir / case_name


def ListCases(tests_dir: pl.Path) -> list[pl.Path]:
    return ListSubDir(tests_dir)


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetCorrectOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / CORRECT_OUTPUT_FILE_NAME

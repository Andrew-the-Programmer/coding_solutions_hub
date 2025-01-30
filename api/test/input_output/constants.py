import pathlib as pl
import re
import shutil


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def IsExecutable(path: pl.Path) -> bool:
    return shutil.which(path) is not None


def UserDir(solution_dir: pl.Path) -> pl.Path:
    return solution_dir.parent


def ProblemDir(solution_dir: pl.Path) -> pl.Path:
    return UserDir(solution_dir).parent


def CasesDir(solution_dir: pl.Path) -> pl.Path:
    return ProblemDir(solution_dir) / "test" / "input_output" / "cases"


CASES_DIR = Here() / "cases"
cases_dir = None
OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"
CHECKER = Here() / "checkers" / "basic_checker.py"


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def ListCases() -> list[pl.Path]:
    if not CASES_DIR.is_dir():
        return []
    return sorted([x for x in CASES_DIR.iterdir() if x.is_dir()])


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetCorrectOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / CORRECT_OUTPUT_FILE_NAME

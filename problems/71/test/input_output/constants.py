import pathlib as pl
import re
import shutil


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def IsExecutable(path: pl.Path) -> bool:
    return shutil.which(path) is not None


CASES_DIR = Here() / "cases"
OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"
CHECKER = Here() / "checkers" / "basic_checker.py"
CUSTOM_CHECKER_MATCH = "checker.*"


for f in Here().iterdir():
    if IsExecutable(f) and re.match(CUSTOM_CHECKER_MATCH, f.name):
        CHECKER = f
        break


def GetCasePath(case_name: str) -> pl.Path:
    return CASES_DIR / case_name


def ListCases() -> list[pl.Path]:
    return sorted([x for x in CASES_DIR.iterdir() if x.is_dir()])


def GetInputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / INPUT_FILE_NAME


def GetOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / OUTPUT_FILE_NAME


def GetCorrectOutputFilePath(case_path: pl.Path) -> pl.Path:
    return case_path / CORRECT_OUTPUT_FILE_NAME

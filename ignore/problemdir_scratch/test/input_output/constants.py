import pathlib as pl


def Here() -> pl.Path:
    return pl.Path(__file__).parent


CASES_DIR = Here() / "cases"
OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"
CHECKER = Here() / "checkers" / "basic_checker.py"


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

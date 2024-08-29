import pathlib as pl


def Here() -> pl.Path:
    return pl.Path(__file__).parent


CASES_DIR = Here() / "cases"
OUTPUT_FILE_NAME = "output.txt"
INPUT_FILE_NAME = "input.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"
CHECKER = Here() / "checker.py"

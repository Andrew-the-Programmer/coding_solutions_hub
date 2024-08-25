import pathlib as pl


def Here() -> pl.Path:
    return pl.Path(__file__).parent


ROOT_DIR = Here().parent
OUT_DIR = ROOT_DIR / "out"
BUILD_DIR = OUT_DIR / "build"
SOLUTION_DIR = ROOT_DIR / "solution"
PROJECT_NAME = "Solution"
SOLUTION_EXECUTABLE = BUILD_DIR / PROJECT_NAME
PROBLEM_DIR = ROOT_DIR.parent
TEST_DIR = PROBLEM_DIR / "test"
TEST_EXECUTABLE = TEST_DIR / "main.py"
ZIP_FILE = ROOT_DIR / "solution.zip"

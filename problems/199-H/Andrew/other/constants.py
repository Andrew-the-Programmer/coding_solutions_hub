import pathlib as pl


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def FindUserDir(here: pl.Path) -> pl.Path:
    if here == here.parent:
        ValueError("No user directory found")
    if "CMakeLists.txt" in [x.name for x in here.iterdir()]:
        return here
    return FindUserDir(here.parent)


USER_DIR = FindUserDir(Here())
OUT_DIR = USER_DIR / "out"
BUILD_DIR = OUT_DIR / "build"
DEBUG_DIR = OUT_DIR / "debug"
SOLUTION_DIR = USER_DIR / "solution"
PROJECT_NAME = "Solution"
SOLUTION_EXECUTABLE = BUILD_DIR / PROJECT_NAME
PROBLEM_DIR = USER_DIR.parent
TEST_DIR = PROBLEM_DIR / "test"
TEST_EXECUTABLE = TEST_DIR / "main.py"
ZIP_FILE = USER_DIR / "solution.zip"
ADD_TEST_EXECUTABLE = TEST_DIR / "add_test.py"

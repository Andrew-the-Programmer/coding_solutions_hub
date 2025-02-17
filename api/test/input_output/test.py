import argparse
import pathlib as pl

from my_os import ListSubDir
from project_navigator import FileNavigator

from .check import Check
from .navigator import RootNavigator, TestNavigator
from .run import RunTest


def TestCaseBeginMsg(case_name: str) -> None:
    print(f"=== {case_name} ===")


def TestCase(test_dir: pl.Path, executable: pl.Path):
    test = TestNavigator(test_dir)
    TestCaseBeginMsg(test.Name())
    e = RunTest(test_dir=test_dir, executable=executable)
    if e.returncode == 0:
        Check(test_dir=test_dir)
    return e


def Test(
    *, executable: pl.Path = None, tests_dir: pl.Path = None, file: pl.Path = None
) -> None:
    if file is not None:
        rn = RootNavigator.FindRoot(file)
        tests_dir = rn.TestsDir()
        executable = FileNavigator(file).Runner()
    if executable is None:
        raise ValueError("executable is None")
    if tests_dir is None:
        raise ValueError("tests_dir is None")
    for test_dir in ListSubDir(tests_dir):
        TestCase(test_dir, executable)


def main():
    parser = argparse.ArgumentParser(description="Test all cases")
    parser.add_argument(
        "--executable",
        "-e",
        required=True,
        type=pl.Path,
    )
    parser.add_argument(
        "--tests-dir",
        "-t",
        required=True,
        type=pl.Path,
    )
    args, _ = parser.parse_known_args()
    executable: pl.Path = args.executable
    tests_dir: pl.Path = args.tests_dir
    Test(executable=executable, tests_dir=tests_dir)


if __name__ == "__main__":
    main()

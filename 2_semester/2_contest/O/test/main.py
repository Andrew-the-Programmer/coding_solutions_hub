#!/usr/bin/env python3

import argparse
import pathlib as pl

import backend.main as backend
import input_output.main as input_output


def Here() -> pl.Path:
    return pl.Path(__file__).parent


IO_TEST_DIR = Here() / "input_output"
BACKEND_TEST_DIR = Here() / "backend"


def TestCategoryBeginMsg(test_name: str) -> None:
    print(f"=============== {test_name} ===============")


def TestInputOutput(executable: pl.Path) -> None:
    TestCategoryBeginMsg("INPUT-OUTPUT")
    input_output.Test(executable)


def TestBackend(solution: pl.Path) -> None:
    TestCategoryBeginMsg("BACKEND")
    backend.Test(solution)


def Test(*, executable: pl.Path, solution: pl.Path) -> None:
    if executable is not None:
        TestInputOutput(executable)

    if solution is not None:
        TestBackend(solution)


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--executable",
        "-e",
        type=pl.Path,
        help="Path to the executable. Pass this argument to test input_output.",
        default=None,
    )
    parser.add_argument(
        "--solution",
        "-s",
        type=pl.Path,
        help="Path to the solution directory. Pass this argument to test backend.",
        default=None,
    )

    args = parser.parse_args()

    executable: pl.Path | None = args.executable
    solution: pl.Path | None = args.solution

    Test(executable=executable, solution=solution)


if __name__ == "__main__":
    main()

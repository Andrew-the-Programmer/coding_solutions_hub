#!/usr/bin/env python3

import argparse
import pathlib as pl
import typing

import cpp_backend.main as cpp_backend
import input_output.main as input_output


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def TestCategoryBeginMsg(test_name: str) -> None:
    print(f"=============== {test_name} ===============")


def TestInputOutput(executable: pl.Path) -> None:
    TestCategoryBeginMsg("INPUT-OUTPUT")
    input_output.Test(executable)


def TestBackend(solution: pl.Path, language: typing.Literal["cpp"]) -> None:
    TestCategoryBeginMsg("BACKEND")
    if language == "cpp":
        cpp_backend.Test(solution)


def Test(
    *, executable: pl.Path, solution: pl.Path, language: typing.Literal["cpp"]
) -> None:
    if executable is not None:
        TestInputOutput(executable)

    if solution is not None and language is not None:
        TestBackend(solution, language)


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
    parser.add_argument(
        "--language",
        "-l",
        type=str,
        help="Language of the solution. Pass this argument to test backend.",
        default="cpp",
    )

    args = parser.parse_args()

    executable: pl.Path | None = args.executable
    solution: pl.Path | None = args.solution
    language: str | None = args.language

    Test(executable=executable, solution=solution, language=language)


if __name__ == "__main__":
    main()

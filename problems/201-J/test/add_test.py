#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

ADD_TEST_EXECUTABLE = "add_test.py"
CATEGORY_ARG_NAME = "category"


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def ListCategories() -> list[str]:
    return sorted([x.name for x in Here().iterdir() if x.is_dir()])


def _Select(options: list[str], prompt: str = ">") -> str:
    input_str = "\n".join(options)
    # input_str = "hello world\nbye world"
    process = subprocess.run(
        ["fzf", "--prompt", prompt],
        input=input_str,
        text=True,
        encoding="utf-8",
        stdout=subprocess.PIPE,
        check=False,
    )
    output = process.stdout.split("\n")[0]
    return output


def Select(
    options: list[str],
    *,
    target: str = None,
    prompt: str = None,
) -> str:
    if target is None:
        target = "option"

    if prompt is None:
        prompt = f"Select {target}>"

    selected = _Select(options, prompt=prompt)
    return selected


def AskCategory() -> str:
    return Select(ListCategories(), target="category")


def AddTest(category: str | None, args: list[str]) -> None:
    if category is None:
        category = AskCategory()
    category_dir = Here() / category
    return subprocess.run(
        [
            category_dir / ADD_TEST_EXECUTABLE,
        ]
        + list(args),
        check=False,
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        CATEGORY_ARG_NAME,
        default=None,
        nargs="?",
        help="Test category",
    )
    args, known_args = parser.parse_known_args()
    category: str | None = args.__dict__[CATEGORY_ARG_NAME]
    AddTest(category, known_args)


if __name__ == "__main__":
    main()

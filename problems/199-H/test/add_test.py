#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

ADD_TEST_EXECUTABLE = "add_test.py"


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


def AddTest(category: str | None) -> None:
    if category is None:
        category = AskCategory()
    category_dir = Here() / category
    return subprocess.run(
        [
            category_dir / ADD_TEST_EXECUTABLE,
        ],
        check=True,
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "category",
        default=None,
        nargs="?",
        help="Test category",
    )

    args = parser.parse_args()

    category: str | None = args.category
    if category == "":
        category = None

    AddTest(category)


if __name__ == "__main__":
    main()

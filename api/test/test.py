#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess

TEST_EXECUTABLE = "test.py"
CATEGORY_ARG_NAME = "test_category"


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def ListCategories() -> list[str]:
    return sorted([x.name for x in Here().iterdir() if x.is_dir()])


def SelectFzf(options: list[str], prompt: str = ">") -> str:
    input_str = "\n".join(options)
    process = subprocess.run(
        ["fzf", "--prompt", prompt],
        input=input_str,
        text=True,
        encoding="utf-8",
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        check=False,
    )
    return process.stdout.split("\n")[0]


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
    return SelectFzf(options, prompt=prompt)


def AskCategory() -> str:
    return Select(ListCategories(), target="category")


def TestCategoryBeginMsg(test_name: str) -> None:
    print(f"=============== {test_name} ===============")


def Test(category: str | None, args: list[str]) -> None:
    TestCategoryBeginMsg(category)
    if category is None:
        category = AskCategory()
    category_dir = Here() / category
    return subprocess.run(
        [
            category_dir / TEST_EXECUTABLE,
        ]
        + list(args),
        check=False,
    )


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        f"--{CATEGORY_ARG_NAME}",
        default="all",
        nargs="?",
        help="Test category",
    )
    args, known_args = parser.parse_known_args()
    category: str | None = args.__dict__[CATEGORY_ARG_NAME]

    if category == "all":
        for c in ListCategories():
            try:
                Test(c, known_args)
            except Exception as e:
                print(e)
    else:
        Test(category, known_args)


if __name__ == "__main__":
    main()

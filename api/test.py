#!/usr/bin/env python3

import argparse
import pathlib as pl
from importlib import import_module

from project_navigator import FileNavigator


def TestCategoryBeginMsg(test_name: str) -> None:
    print(f"=============== {test_name} ===============")


def Test(category: str, *args, **kwargs) -> None:
    TestCategoryBeginMsg(category)
    try:
        import_module(f"test.{category}").Test(*args, **kwargs)
    except AttributeError as e:
        print(e)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("file", type=pl.Path, default=None)
    parser.add_argument("--category", type=str, default="all")
    args = parser.parse_args()
    file: pl.Path = args.file
    category: str = args.category
    fn = FileNavigator(file)
    tests = fn.Problem().Tests()
    categories = tests.Categories() if category == "all" else [category]
    for c in categories:
        Test(c, file=file)


if __name__ == "__main__":
    main()

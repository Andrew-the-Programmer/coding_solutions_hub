#!/usr/bin/env python3

import argparse
import pathlib as pl
from importlib import import_module

from my_select import Select
from project_navigator import ProjectNavigator


def AddTest(category: str, *args, **kwargs) -> None:
    import_module(f"test.{category}").AddTest(*args, **kwargs)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("file", type=pl.Path, default=None)
    parser.add_argument("--category", type=str, default=None)
    args = parser.parse_args()
    file: pl.Path = args.file
    category: str = args.category
    if category is None:
        categories = ProjectNavigator.TestCategories()
        category = Select(categories, ask_new=False)
    AddTest(category, file=file)


if __name__ == "__main__":
    main()

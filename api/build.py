#!/usr/bin/env python3

import argparse
import pathlib as pl
from importlib import import_module


def Build(file: pl.Path):
    ext = file.suffix[1:]
    import_module(ext).Build(file)


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("file", type=pl.Path, default=None)
    args = parser.parse_args()
    file: pl.Path = args.file
    Build(file)


if __name__ == "__main__":
    main()

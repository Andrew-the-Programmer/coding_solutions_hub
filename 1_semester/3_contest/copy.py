#!/usr/bin/env python3

import pathlib as pl
import shutil


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def Copy() -> None:
    desc_dir: pl.Path = Here() / "desc"
    for f in desc_dir.iterdir():
        letter = f.name[0]
        problem = None
        for d in Here().iterdir():
            if d.is_dir() and d.name[0] == letter:
                problem = d
        if not problem:
            problem = Here() / letter
        problem.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(f, problem / "desc_ru.html")


def main() -> None:
    Copy()


if __name__ == "__main__":
    main()

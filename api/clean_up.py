#!/usr/bin/env python3


import pathlib as pl
import subprocess
import re

from my_os import Delete, IsEmptyDir, ListDir, ListDirRecursive, Rename
from project_navigator import (HeroNavigator, ProblemNavigator,
                               ProjectNavigator, TestsNavigator)


def FormatREADME(path: pl.Path):
    return subprocess.run(["mdformat", path], check=True)


def CleanHero(hn: HeroNavigator):
    for f in ListDir(hn.Path()):
        if f.is_dir() and f.name == "other":
            Delete(f)
        if f.name == "CMakeLists.txt":
            Delete(f)
        if f.is_dir() and f.name == "out":
            Delete(f)


def CleanTests(tn: TestsNavigator):
    for f in ListDir(tn.Path()):
        if f.name != "input_output":
            Delete(f)
    io = tn.Path() / "input_output"
    for f in ListDir(io):
        if f.name not in ["cases", "tests"]:
            Delete(f)
    cases = io / "cases"
    if not IsEmptyDir(cases):
        print("tests exist")
        Rename(cases, "tests")
    else:
        Delete(tn.Path())


def CleanProblem(pn: ProblemNavigator):
    print(pn.Path())
    for hn in pn.Heroes():
        CleanHero(hn)
    tn = pn.Tests()
    CleanTests(tn)
    for f in ListDirRecursive(pn.Path()):
        if f.name == "README.md":
            FormatREADME(f)
    for f in ListDir(pn.Path()):
        if re.match(r"desc.*\.html", f.name):
            print(f.name)
            Rename(f, "description.html")


def main() -> None:
    for pn in ProjectNavigator.Problems():
        CleanProblem(pn)


if __name__ == "__main__":
    main()

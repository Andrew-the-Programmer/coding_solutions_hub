#!/usr/bin/env python3

import argparse
import pathlib as pl

from creat_problem import SelectProblem
from my_os import Format, ListSubDir
from my_select import Select
from project_navigator import ProblemReference, ProjectNavigator


def AskLinkName() -> str:
    msg = """
Enter new link name. Try to name it "<letter>-<description>"
>"""
    name = input(msg)
    print(f"New link name is: {name}")
    return name


def AskNewDirName() -> str:
    msg = """Enter new directory name >"""
    print(msg, end="")
    name = input()
    print(f"New directory name is: {name}")
    return name


def SelectDir(start: pl.Path) -> pl.Path:
    def on_new():
        name = AskNewDirName()
        path = start / name
        path.mkdir(parents=True, exist_ok=True)
        return path

    return Select(
        [p.name for p in ListSubDir(start)],
        prompt=f"{start}/",
        on_new=on_new,
    )


def FindDir(start: pl.Path) -> pl.Path:
    option_here = "<here>"
    s = None
    while True:
        s = Select(
            [p.name for p in ListSubDir(start)] + [option_here],
            prompt=f"{start}/",
        )
        if s == option_here:
            return start
        s = Format(s)
        start = start / s


def AskLinkPath() -> pl.Path:
    target = FindDir(ProjectNavigator.CoursesDir())
    link_name = AskLinkName()
    return target / link_name


def CreateLink(problem_name: str, link: pl.Path) -> None:
    link = ProblemReference(link)
    link.AddProblem(problem_name)


def main():
    parser = argparse.ArgumentParser(
        description="Create a link to the problem")
    parser.add_argument(
        "--target",
        type=pl.Path,
        help="""
            Path to the destination in ROOT/courses/.../<link name>/
            """,
        default=None,
    )
    parser.add_argument(
        "--problem",
        type=pl.Path,
        help="""
            problem name in ROOT/problems/<problem name>/
            """,
        default=None,
    )
    args = parser.parse_args()
    link_path: pl.Path | None = args.target
    problem_name: pl.Path | None = args.problem

    if not problem_name:
        problem_name = SelectProblem(ask_new=False).Name()

    if link_path is None:
        link_path = AskLinkPath()

    CreateLink(problem_name, link_path)


if __name__ == "__main__":
    main()

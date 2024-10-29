#!/bin/python3

import argparse
import pathlib as pl

from constants import PROBLEMS_DIR
from iterate_project import GetAllProblems, GetUniqueProblemId
from my_select import Confirm, Select
from update import UpdateProblem

import create_link


def Format(name: str) -> str:
    return name.replace(" ", "_")


def CreateProblemName(pid: str = None, desc: str = None) -> str:
    if not pid:
        pid = f"{GetUniqueProblemId()}"
    name = Format(pid)
    if desc:
        name += f"{name}-{Format(desc)}"
    return name


def InputNewProblemName() -> str:
    msg = """
Enter problem name. If new name dont start with number,
unique id will be prepended. You could use existing id, this would indicate
that your problem is a slight variation of another.
"""
    # print(msg)
    desc = input("Input short problem description (optional): ")
    pid = input("Input problem id (or press enter to generate new id): ")
    name = CreateProblemName(pid, desc)
    print(f"New problem name is: {name}")
    return name


def SelectProblem(target_path: pl.Path) -> None:
    problem_name = Select(
        [p.name for p in GetAllProblems(target_path)],
        target="problem",
        on_new=InputNewProblemName,
    )
    problem_path = target_path / problem_name
    return problem_path


def AskProblemPath(problem_path: pl.Path) -> pl.Path:
    if problem_path:
        return problem_path
    problem_name = SelectProblem(PROBLEMS_DIR)
    problem_path = PROBLEMS_DIR / problem_name
    return problem_path


def CreateLink(problem_path: pl.Path, persist: bool | None) -> None:
    if persist is None:
        persist = Confirm("Would you like to create link to the problem? ")
    if not persist:
        return
    create_link.CreateLink(problem_path, None)


def CreateProblem(problem_path: pl.Path | None) -> None:
    problem_path = AskProblemPath(problem_path)
    UpdateProblem(problem_path)


def main() -> None:
    parser = argparse.ArgumentParser(description="")
    parser.add_argument("--new-problem", action="store_true", default=False)
    parser.add_argument(
        "--problem-name",
        type=str,
        help="""
            Problem name
            (./problems/<problem_name>)
            """,
        default=None,
    )
    parser.add_argument(
        "--problem-path",
        type=pl.Path,
        help="""
            Path to the problem
            (f.e. ./problems/<problem_name>)
            """,
        default=None,
    )
    parser.add_argument("--create-link", action="store_true", default=False)

    args: argparse.Namespace = parser.parse_args()

    problem_name: str | None = args.problem_name
    problem_path: pl.Path | None = args.problem_path
    link: bool = args.create_link
    new_problem: bool = args.new_problem

    if new_problem:
        problem_name = CreateProblemName()

    if problem_path is None and problem_name is not None:
        problem_path = PROBLEMS_DIR / problem_name

    problem_path = AskProblemPath(problem_path)

    CreateProblem(problem_path)
    CreateLink(problem_path, link)


if __name__ == "__main__":
    main()

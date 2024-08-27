#!/bin/python3

import argparse
import pathlib as pl
import re
import typing

import git
from constants import CONTRIBUTORS_DIR, PROBLEMS_DIR
from iterate_project import GetAllProblemIds, GetAllProblems, GetContributors
from my_select import Select
from update import UpdateProblem, UpdateUserDir, UpdateContributor


def SelectUsername(args) -> None:
    username: str | None = args.username
    if username:
        return
    username = Select(
        GetContributors(),
        target="username",
    )
    args.username = username


def GetNewProblemId() -> int:
    ids = GetAllProblemIds()
    return 0 if len(ids) == 0 else max(ids) + 1


def Format(name: str) -> str:
    return name.replace(" ", "_")

def CreateProblemName(pid: str, desc: str) -> str:
    return f"{Format(pid)}-{Format(desc)}"


def AskForNewProblemName() -> str:
    msg = """
Enter problem name. If new name dont start with number,
unique id will be prepended. You could use existing id, this would indicate
that your problem is a slight variation of another.
    """
    # print(msg)
    desc = input("Input short problem description (optional): ")
    pid = input("Input problem id (or press enter to generate new id): ")
    if not pid:
        pid = f"{GetNewProblemId()}"
    name = CreateProblemName(pid, desc)

    print(f"New problem name is: {name}")

    return name


def SelectProblem(args) -> None:
    problem_name: str | None = args.problem_name
    if problem_name:
        return
    problem_name = Select(
        [x.name for x in GetAllProblems()],
        target="problem",
        on_new=AskForNewProblemName,
    )
    args.problem_name = problem_name


def AskArgs(args) -> None:
    if args.problem_path:
        args.problem_name = args.problem_path.name
    SelectUsername(args)
    SelectProblem(args)
    args.problem_path = PROBLEMS_DIR / args.problem_name
    args.userdir_path = args.problem_path / args.username


def CreateSolution(args) -> None:
    UpdateContributor(CONTRIBUTORS_DIR / args.username)
    UpdateProblem(args.problem_path)
    UpdateUserDir(args.userdir_path)


def main() -> None:
    parser = argparse.ArgumentParser(description="Get site html")
    parser.add_argument(
        "--username",
        "-u",
        type=str,
        help="Name of the contributor",
        default=None,
    )
    parser.add_argument(
        "--problem-name",
        "-p",
        type=str,
        help="Name of the problem",
        default=None,
    )
    parser.add_argument(
        "--problem-path",
        type=pl.Path,
        help="""
            Path to the problem
            (./problems/<problem_name>)
            f.e. ./2_semester/1_contest/C""",
        default=None,
    )
    parser.add_argument(
        "--branch-name",
        "-b",
        type=str,
        help="Git branch. All commited on this branch.",
        default="dev",
    )

    args: argparse.Namespace = parser.parse_args()

    AskArgs(args)
    CreateSolution(args)


if __name__ == "__main__":
    main()

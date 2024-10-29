#!/bin/python3

import argparse
import pathlib as pl

from constants import CONTRIBUTORS_DIR, PROBLEMS_DIR
from iterate_project import GetAllProblems, GetContributors, GetUniqueProblemId
from my_select import Confirm, Select
from update import UpdateContributor, UpdateProblem, UpdateUserDir

import create_link


def Format(name: str) -> str:
    return name.replace(" ", "_")


def CreateProblemName(pid: str = None, desc: str = None) -> str:
    if not pid:
        pid = f"{GetUniqueProblemId()}"
    name = Format(pid)
    if desc:
        name = f"{name}-{Format(desc)}"
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


def SelectUsername() -> str:
    username = Select(
        GetContributors(),
        target="username",
    )
    return username


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


def AskUsername(username: str) -> str:
    if username:
        return username
    username = SelectUsername()
    return username


def AskUserdir(userdir_path: pl.Path) -> pl.Path:
    if userdir_path:
        return userdir_path
    username = AskUsername(None)
    problem_path = AskProblemPath(None)
    userdir_path = problem_path / username
    return userdir_path


def CreateLink(problem_path: pl.Path, persist: bool | None) -> None:
    if persist is None:
        persist = Confirm("Would you like to create link to the problem? ")
    if not persist:
        return
    create_link.CreateLink(problem_path, None)


def CreateSolution(userdir_path: pl.Path | None) -> None:
    userdir_path = AskUserdir(userdir_path)
    username = userdir_path.name
    problem_path = userdir_path.parent
    UpdateProblem(problem_path)
    UpdateUserDir(userdir_path)
    UpdateContributor(CONTRIBUTORS_DIR / username)


def main() -> None:
    parser = argparse.ArgumentParser(description="Get site html")
    parser.add_argument(
        "--userdir-path",
        type=pl.Path,
        help="""
            Path to the userdir
            (./problems/<problem_name>/<username>)
            """,
        default=None,
    )
    parser.add_argument("--create-link", action="store_true", default=False)

    args: argparse.Namespace = parser.parse_args()

    userdir_path: pl.Path | None = args.userdir_path
    link: bool = args.create_link

    userdir_path = AskUserdir(userdir_path)
    problem_path = userdir_path.parent

    CreateSolution(userdir_path)
    CreateLink(problem_path, link)


if __name__ == "__main__":
    main()

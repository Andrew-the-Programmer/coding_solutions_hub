#!/bin/python3

import argparse
import pathlib as pl

from my_os import Format
from my_select import Select
from project_navigator import ProblemNavigator, ProjectNavigator


def GetUniqueProblemId() -> int:
    m = None
    for p in ProjectNavigator.Problems():
        i = p.Id()
        if i is not None and (m is None or i > m):
            m = i
    return m + 1


def GetProblemName(id_str: str = None, desc: str = None) -> str:
    if not id_str:
        id_str = f"{GetUniqueProblemId()}"
    name = id_str
    if desc:
        name = f"{name}-{Format(desc)}"
    return name


def AskProblemName() -> str:
    """
    Enter problem name. If new name dont start with number,
    unique id will be prepended. You could use existing id, this would indicate
    that your problem is a slight variation of another.
    """
    # print(msg)
    # pid = input("Input problem id (or press enter to generate new id): ")
    pid = None
    desc = input("Input short problem description (optional): ")
    name = GetProblemName(pid, desc)
    print(f"New problem name is: {name}")
    return name


def SelectProblem(ask_new: bool = True) -> ProblemNavigator:
    problem_name = Select(
        [p.Name() for p in ProjectNavigator.Problems()],
        target="problem",
        ask_new=ask_new,
        on_new=AskProblemName,
    )
    return ProjectNavigator.GetProblem(problem_name)


def CreateProblem(problem_name: str) -> ProblemNavigator:
    problem = ProjectNavigator.GetProblem(problem_name)
    problem.Create()
    return problem


def main() -> None:
    parser = argparse.ArgumentParser(description="Create new problem")
    parser.add_argument(
        "--problem-name",
        help="'new' for generating new problem name",
        default=None,
    )

    args = parser.parse_args()
    problem_name: str = args.problem_name

    if problem_name == "new":
        problem_name = GetProblemName()

    if not problem_name:
        problem_name = AskProblemName()

    CreateProblem(problem_name)


if __name__ == "__main__":
    main()

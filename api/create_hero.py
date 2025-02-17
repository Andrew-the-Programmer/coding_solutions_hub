#!/bin/python3

import argparse

from create_problem import GetProblemName, SelectProblem
from my_select import Select
from project_navigator import ProjectNavigator


def SelectHero() -> str:
    return Select(
        ProjectNavigator.Heroes(),
        target="username",
    )


def CreateHero(problem_name: str, hero: str) -> None:
    problem = ProjectNavigator.GetProblem(problem_name)
    problem.Update()
    problem.AddHero(hero)


def main() -> None:
    parser = argparse.ArgumentParser(description="Create new hero")
    parser.add_argument(
        "--problem",
        help="'new' for generating new problem name",
        default=None,
    )
    parser.add_argument(
        "--hero",
        default=None,
    )

    args = parser.parse_args()
    problem_name: str | None = args.problem
    hero: str | None = args.hero

    if problem_name == "new":
        problem_name = GetProblemName()

    if not problem_name:
        problem_name = SelectProblem().Name()

    if not hero:
        hero = SelectHero()

    CreateHero(problem_name, hero)


if __name__ == "__main__":
    main()

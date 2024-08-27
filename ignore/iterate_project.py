#!/bin/python3

import itertools
import pathlib as pl
import re

from constants import (
    CONTEST_POSTFIX,
    CONTRIBUTORS_DIR,
    PROBLEMS_DIR,
    REPO_DIR,
    SEMESTER_POSTFIX,
)

DESCRIPTIONS_DIR_NAME = "_DESCRIPTIONS_"

flatten = itertools.chain.from_iterable


def ListDir(path: pl.Path) -> list[pl.Path]:
    return sorted(path.iterdir() if path.is_dir() else [])


def ListDirRecursive(path: pl.Path) -> list[pl.Path]:
    for p in path.iterdir():
        if p.is_dir():
            yield from ListDirRecursive(p)
        yield p


def GetAllProblems() -> list[pl.Path]:
    return ListDir(PROBLEMS_DIR)


def GetContributors() -> list[str]:
    return [x.name for x in ListDir(CONTRIBUTORS_DIR)]


def Semesters(path: pl.Path) -> list[pl.Path]:
    dirs = ListDir(path)
    return [x for x in dirs if x.name.endswith(SEMESTER_POSTFIX)]


def Contests(semester_path: pl.Path) -> list[pl.Path]:
    dirs = ListDir(semester_path)
    return [x for x in dirs if x.name.endswith(CONTEST_POSTFIX)]


def Problems(contest_path: pl.Path) -> list[pl.Path]:
    dirs = ListDir(contest_path)
    return [x for x in dirs if x.name != DESCRIPTIONS_DIR_NAME]


def UserDirs(problem_path: pl.Path) -> list[pl.Path]:
    dirs = ListDir(problem_path)
    return [x for x in dirs if x.name in GetContributors()]


def AllCourses() -> list[pl.Path]:
    courses = ["cpp", "algorithms"]
    return [REPO_DIR / course for course in courses]


def AllSemesters() -> list[pl.Path]:
    return flaten(Semesters(course) for course in AllCourses())


def AllContests() -> list[pl.Path]:
    return flatten(Contests(x) for x in AllSemesters())


def AllProblems() -> list[pl.Path]:
    return flatten(Problems(x) for x in AllContests())


def AllUserDirs() -> list[pl.Path]:
    return flatten(UserDirs(x) for x in AllProblems())


def GetProblemId(problem_name: str) -> int:
    problem_id = int(re.match(r"(\d+)", problem_name)[1])
    return problem_id


def GetAllProblemIds() -> list[int]:
    return sorted([GetProblemId(p.name) for p in GetAllProblems()])

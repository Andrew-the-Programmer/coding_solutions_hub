#!/bin/python3

import itertools
import pathlib as pl
import re

from constants import (CONTEST_POSTFIX, CONTRIBUTORS_DIR, PROBLEMS_DIR,
                       REPO_DIR, SEMESTER_POSTFIX)

DESCRIPTIONS_DIR_NAME = "_DESCRIPTIONS_"

flatten = itertools.chain.from_iterable


def ListDir(path: pl.Path) -> list[pl.Path]:
    return sorted(path.iterdir() if path.is_dir() else [])


def ListDirRecursive(path: pl.Path) -> list[pl.Path]:
    for p in path.iterdir():
        if p.is_dir():
            yield from ListDirRecursive(p)
        yield p


def GetAllProblems(path: pl.Path = PROBLEMS_DIR) -> list[pl.Path]:
    return ListDir(path)


def GetContributors() -> list[str]:
    return [x.name for x in ListDir(CONTRIBUTORS_DIR)]


def Courses(path: pl.Path = REPO_DIR) -> list[pl.Path]:
    courses = ["cpp", "algorithms"]
    return [path / n for n in courses]


def Semesters(course_path: pl.Path) -> list[pl.Path]:
    dirs = ListDir(course_path)
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
    return flatten(Courses(REPO_DIR))


def AllSemesters() -> list[pl.Path]:
    return flatten(Semesters(course) for course in AllCourses())


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


def GetUniqueProblemId() -> int:
    ids = GetAllProblemIds()
    return 0 if len(ids) == 0 else max(ids) + 1

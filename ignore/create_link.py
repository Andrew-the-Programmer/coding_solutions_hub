#!/usr/bin/env python3

import argparse
import pathlib as pl

from constants import (
    CONTEST_POSTFIX,
    PROBLEMS_DIR,
    REPO_DIR,
    SEMESTER_POSTFIX,
)
from iterate_project import (
    Contests,
    Courses,
    GetAllProblems,
    Semesters,
)
from my_select import Select
from os_functions import Link, RelativePath


def InputNewCourse() -> str:
    msg = """
Enter course name
>"""
    print(msg, end="")
    name = input()
    print(f"New course name is: {name}")
    return name


def InputNewSemester() -> str:
    msg = f"""
Enter semester name. If new name dont end with "{SEMESTER_POSTFIX}",
it will be appended.
>"""
    print(msg, end="")
    name = input()
    if not name.endswith(SEMESTER_POSTFIX):
        name += SEMESTER_POSTFIX
    print(f"New semester name is: {name}")
    return name


def InputNewContest() -> str:
    msg = f"""
Enter contest name. If new name dont end with "{CONTEST_POSTFIX}",
it will be appended.
>"""
    print(msg, end="")
    name = input()
    if not name.endswith(CONTEST_POSTFIX):
        name += CONTEST_POSTFIX
    print(f"New contest name is: {name}")
    return name


def SelectCourse(target_path: pl.Path) -> None:
    course_name = Select(
        [c.name for c in Courses(target_path)],
        target="course",
        on_new=InputNewCourse,
    )
    course_path = target_path / course_name
    return course_path


def SelectSemester(target_path: pl.Path) -> None:
    semester_name = Select(
        [s.name for s in Semesters(target_path)],
        target="semester",
        on_new=InputNewSemester,
    )
    semester_path = target_path / semester_name
    return semester_path


def SelectContest(target_path: pl.Path) -> None:
    contest_name = Select(
        [s.name for s in Contests(target_path)],
        target="contest",
        on_new=InputNewContest,
    )
    contest_path = target_path / contest_name
    return contest_path


def SelectProblem(target_path: pl.Path) -> None:
    problem_name = Select(
        [p.name for p in GetAllProblems(target_path)],
        target="problem",
        ask_new=False,
    )
    problem_path = target_path / problem_name
    return problem_path


def InputLinkName() -> str:
    msg = """
Enter new link name. Try to name it "<letter>-<description>"
>"""
    print(msg, end="")
    name = input()
    print(f"New link name is: {name}")
    return name


def AskLinkPath(link_path: pl.Path) -> pl.Path:
    if link_path:
        return link_path
    course = SelectCourse(REPO_DIR)
    semester = SelectSemester(course)
    contest = SelectContest(semester)
    link_name = InputLinkName()
    link_path = contest / link_name
    return link_path


def AskProblemPath(problem_path: pl.Path) -> pl.Path:
    if problem_path:
        return problem_path
    problem_name = SelectProblem(PROBLEMS_DIR)
    problem_path = PROBLEMS_DIR / problem_name
    return problem_path


def CreateLink(problem_path: pl.Path, link_path: pl.Path) -> None:
    problem_path = AskProblemPath(problem_path)
    link_path = AskLinkPath(link_path)
    link_path.parent.mkdir(exist_ok=True, parents=True)
    rpath = RelativePath(link_path.parent, problem_path)
    Link(rpath, link_path)


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Create a link to the problem")
    parser.add_argument(
        "--link-path",
        type=pl.Path,
        help="""
            Path to the contest
            (./<course>/<semester>/<contest>)
            """,
        default=None,
    )
    parser.add_argument(
        "--problem-path",
        type=pl.Path,
        help="""
            Path to the problem
            (./problems/<problem_name>)
            """,
        default=None,
    )
    args = parser.parse_args()
    link_path: pl.Path | None = args.link_path
    problem_path: pl.Path | None = args.problem_path
    CreateLink(problem_path, link_path)


if __name__ == "__main__":
    main()

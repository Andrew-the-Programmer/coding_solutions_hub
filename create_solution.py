#!/bin/python3

import argparse
import pathlib as pl
import subprocess
from typing import Any, Iterable

import git
import inquirer

import ignore


def Here() -> pl.Path:
    return pl.Path(__file__).parent


REPO_DIR = Here()
IGNORE_DIR = REPO_DIR / "ignore"
CONTRIBUTORS_DIR = IGNORE_DIR / "contributors"
PROBLEM_DIR_SCRATCH = IGNORE_DIR / "problem_scratch"
USER_DIR_SCRATCH = IGNORE_DIR / "solution_scratch"


def Select(options: list[str], target: str, ask_new: bool) -> str:
    new_option_name = "<new>"
    if ask_new:
        options.append(new_option_name)
    questions = [
        inquirer.List(
            target,
            message=f"Select {target}:",
            choices=options,
        ),
    ]
    answers = inquirer.prompt(questions)
    selected = answers[target]

    if ask_new and selected == new_option_name:
        selected = input(f"Enter new {target}: ")
        if not selected or selected in options:
            raise ValueError(f"Invalid new {target}: {selected}")

    return selected


def ListDir(path: pl.Path) -> list[str]:
    return [x.name for x in path.iterdir() if x.is_dir()] if path.is_dir() else []


def ListContributors(args) -> Iterable[str]:
    return ListDir(CONTRIBUTORS_DIR)


def ListSemesters(args) -> Iterable[str]:
    dirs = ListDir(REPO_DIR)
    return [x for x in dirs if x.endswith("_semester")]


def ListContests(args) -> Iterable[str]:
    semester_dir = REPO_DIR / args.semester
    dirs = ListDir(semester_dir)
    return [x for x in dirs if x.endswith("_contest")]


def ListProblems(args) -> Iterable[str]:
    contest_dir = REPO_DIR / args.semester / args.contest
    return ListDir(contest_dir)


def SetupGit(args) -> None:
    subprocess.run([IGNORE_DIR / "require_clean_work_tree.sh"]).check_returncode()
    args.repo = git.Repo(REPO_DIR)
    branch = args.repo.branches[args.branch_name]
    branch.checkout()


def AskArgs(args) -> None:
    if args.problemdir_path:
        ptp = args.problemdir_path
        args.problem = ptp.name
        args.contest = ptp.parent.name
        args.semester = ptp.parent.parent.name
    if not args.username:
        args.username = Select(
            ListContributors(args),
            "username",
            ask_new=True,
        )
    if not args.semester:
        args.semester = Select(
            ListSemesters(args),
            "semester",
            ask_new=True,
        )
    if not args.contest:
        args.contest = Select(
            ListContests(args),
            "contest",
            ask_new=True,
        )
    if not args.problem:
        args.problem = Select(
            ListProblems(args),
            "problem",
            ask_new=True,
        )
    args.problemdir_path = REPO_DIR / args.semester / args.contest / args.problem
    args.userdir_path = args.problemdir_path / args.username


def CopyContents(*, src: pl.Path, dst: pl.Path) -> Any:
    # Please be careful modifying this function
    return subprocess.run(["cp", "-arn", f"{src}/.", f"{dst}/."])


def CreateSolution(args) -> None:
    contributor_dir = CONTRIBUTORS_DIR / args.username

    # Create new contributor
    contributor_dir.mkdir(parents=True, exist_ok=True)

    ignore.problemdir_scratch.export.Export(
        problemdir=args.problemdir_path, userdir=args.userdir_path
    )


def CommitChages(args) -> None:
    repo: git.Repo = args.repo
    repo.git.add(args.problemdir_path)
    repo.index.commit(
        f"\
{args.branch_name}: {args.semester}/{args.contest}/{args.problem}: \
{args.username}: INITIAL COMMIT"
    )


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
        "--semester",
        "-s",
        type=str,
        help="Semester. Dir of the semester: <semester>_semester",
        default=None,
    )
    parser.add_argument(
        "--contest",
        "-c",
        type=str,
        help="Contest. Dir of the contest: <contest>_contest",
        default=None,
    )
    parser.add_argument(
        "--problem",
        "-p",
        type=str,
        help="Name of the problem",
        default=None,
    )
    parser.add_argument(
        "--path-to-problem",
        type=pl.Path,
        help="""
            Path to the problem
            (./<semester>/<contest>/<problem>)
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

    SetupGit(args)
    AskArgs(args)
    CreateSolution(args)
    CommitChages(args)


if __name__ == "__main__":
    main()

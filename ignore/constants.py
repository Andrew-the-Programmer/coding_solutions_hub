#!/bin/python3

from os_functions import Here

REPO_DIR = Here().parent
IGNORE_DIR = REPO_DIR / "ignore"
CONTRIBUTORS_DIR = IGNORE_DIR / "contributors"
PROBLEM_DIR_SCRATCH = IGNORE_DIR / "problemdir_scratch"
USER_DIR_SCRATCH = IGNORE_DIR / "userdir_scratch"
SEMESTER_POSTFIX = "_semester"
CONTEST_POSTFIX = "_contest"
PROBLEMS_DIR = REPO_DIR / "problems"

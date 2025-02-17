#!/usr/bin/env python3


import pathlib as pl
import re
import subprocess

import markdownify
from my_os import Copy, ListDir
from project_navigator import (ProblemNavigator, ProblemReference,
                               ProjectNavigator)

from create_link import CreateLink

DESC_FILE = "description.html"
README_FILE = "README.md"


def GetMarkdownFromHtml(html: str) -> str:
    return markdownify.markdownify(html)


def FormatREADME(path: pl.Path):
    return subprocess.run(["mdformat", path], check=True)


def CreateREADME(pn: ProblemNavigator):
    desc = pn.Path() / DESC_FILE
    readme = pn.Path() / README_FILE
    if not desc.exists():
        return
    md_text = GetMarkdownFromHtml(desc.read_text())
    readme.write_text(md_text)
    FormatREADME(pn.Path() / README_FILE)


def DescName(path: pl.Path):
    m = re.match(r"([A-Z]+).*\.html", path.name)
    if m:
        return m[1]
    return None


def FindLink(path: pl.Path, name: str) -> ProblemReference:
    return next(
        (
            ProblemReference(f)
            for f in ListDir(path)
            if f.is_dir() and re.match(rf"{name}?-.*", f.name)
        ),
        None,
    )


def GetDescFiles(path: pl.Path):
    return [f for f in ListDir(path) if re.match(r".*\.html", f.name)]


def ProblemName(path: pl.Path):
    m = re.match(r"[0-9]+-([A-Z]+).*", path.name)
    if m:
        return m[1]
    return None


def FindProblem(name: str):
    id_range = range(174, 192)
    return next(
        (
            pn
            for pn in ProjectNavigator.Problems()
            if name == ProblemName(pn.Path()) and pn.Id() in id_range
        ),
        None,
    )


def AddDesc(pn: ProblemNavigator, desc: pl.Path):
    Copy(src=desc, dst=pn.Path() / DESC_FILE)
    CreateREADME(pn)


def AddDescLink(link: ProblemReference, desc: pl.Path):
    AddDesc(pn=ProblemNavigator(link.Path()), desc=desc)


def CreateLinks(
    *, desc: pl.Path, link: ProblemReference = None, pn: ProjectNavigator = None
):
    root = desc.parent
    name = DescName(desc)
    if link is None:
        link = FindLink(root, name)
    if pn is None:
        pn = FindProblem(name)
    if link is not None:
        print(name)
        link.Create()
        if pn is not None:
            CreateLink(pn.Name(), link.Path())
        AddDescLink(link, desc)
        return
    link = ProblemReference(root / name)
    CreateLinks(desc=desc, link=link, pn=pn)


def main() -> None:
    contest = ProjectNavigator.CoursesDir() / "mipt_algorithms" / \
        "3_semester" / "1_contest"
    for desc in GetDescFiles(contest):
        CreateLinks(desc=desc)


if __name__ == "__main__":
    main()

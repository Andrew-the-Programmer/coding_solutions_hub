#!/usr/bin/env python3

import pathlib as pl
import re

from constants import (
    CONTRIBUTORS_DIR,
    PROBLEM_DIR_SCRATCH,
    PROBLEMS_DIR,
    USER_DIR_SCRATCH,
)
from os_functions import Copy, CopyContents, Here


def CopyHard(src: pl.Path, dst: pl.Path) -> None:
    return Copy(src=src, dst=dst, flags="-arf")


def Match(path: pl.Path, patterns: list[str] | None) -> bool:
    if patterns is None:
        return False
    return any(re.search(pattern, str(path)) for pattern in patterns)


def _Update(
    src: pl.Path,
    dst: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    for next_src in src.iterdir():
        next_dst = dst / next_src.name
        if next_dst.exists():
            in_blacklist = Match(next_dst, blacklist)
            in_whitelist = Match(next_dst, whitelist)
            if in_blacklist and in_whitelist:
                ValueError(f"{next_dst} is in blacklist and whitelist")
            if in_blacklist and not in_whitelist:
                continue
            if not in_blacklist and not in_whitelist:
                if whitelist is not None:
                    continue
        if next_src.is_dir():
            next_dst.mkdir(exist_ok=True, parents=True)
            _Update(
                src=next_src, dst=next_dst, blacklist=blacklist, whitelist=whitelist
            )
            continue
        CopyHard(src=next_src, dst=next_dst)


BLACKLIST = [
    # r"README.md",
    r".*",
]
WHITELIST = None


def _UpdateWithDefault(
    src: pl.Path,
    dst: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    _Update(
        src=src,
        dst=dst,
        blacklist=BLACKLIST if blacklist is None else blacklist,
        whitelist=WHITELIST if whitelist is None else whitelist,
    )


def UpdateProblem(
    targetdir: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    _UpdateWithDefault(
        src=PROBLEM_DIR_SCRATCH,
        dst=targetdir,
        blacklist=blacklist,
        whitelist=whitelist,
    )


def UpdateUserDir(
    targetdir: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    _UpdateWithDefault(
        src=USER_DIR_SCRATCH,
        dst=targetdir,
        blacklist=blacklist,
        whitelist=whitelist,
    )


def UpdateContributor(
    targetdir: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    targetdir.mkdir(parents=True, exist_ok=True)

import pathlib as pl
import shutil
import subprocess
from typing import Iterable


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def Copy(
    src: pl.Path, dst: pl.Path, *, flags: str = "-arn"
) -> subprocess.CompletedProcess:
    return subprocess.run(["cp", flags, f"{src}", f"{dst}"])


def CopyAsIs(filename: str, targetdir: pl.Path) -> subprocess.CompletedProcess:
    return Copy(src=Here() / filename, dst=targetdir / filename)


def CopyContents(*, src: pl.Path, dst: pl.Path) -> subprocess.CompletedProcess:
    return subprocess.run(["cp", "-arn", f"{src}/.", f"{dst}/."])


def Link(src: pl.Path, dst: pl.Path) -> subprocess.CompletedProcess:
    return subprocess.run(["ln", "-s", f"{src}", f"{dst}"])


def LinkAsIs(filenames: str, targetdir: pl.Path) -> subprocess.CompletedProcess:
    return Link(src=Here() / filenames, dst=targetdir / filenames)


def CopyAllAsIs(filenames: Iterable[str], targetdir: pl.Path) -> None:
    for filename in filenames:
        CopyAsIs(filename, targetdir)


def LinkAllAsIs(filenames: Iterable[str], targetdir: pl.Path) -> None:
    for filename in filenames:
        LinkAsIs(filename, targetdir)


def CopyDirsLinkFiles(*, src: pl.Path, dst: pl.Path) -> None:
    print(f"{src=}, {dst=}")
    for path in src.iterdir():
        if path.is_dir():
            next_dst = dst / path.name
            next_dst.mkdir(exist_ok=True, parents=True)
            CopyDirsLinkFiles(src=path, dst=next_dst)
        else:
            Link(src=path, dst=dst / path.name)


def Move(src: pl.Path, dst: pl.Path) -> None:
    shutil.move(src, dst)


def RelativePath(From: pl.Path, To: pl.Path) -> pl.Path:
    cur = From
    count = 0
    parents = list(To.parents)
    if To.is_dir():
        parents.append(To)
    while cur not in parents and cur != To:
        count += 1
        cur = cur.parent

    relative = To.relative_to(cur)

    if count == 0:
        return relative

    p = pl.Path("..")
    for _ in range(count - 1):
        p = p / ".."

    result = p / relative
    return result

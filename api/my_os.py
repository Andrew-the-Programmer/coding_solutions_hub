import pathlib as pl
import re
import shutil
import subprocess
from collections.abc import Iterable

from pathvalidate import sanitize_filepath, validate_filename


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def Copy(
    src: pl.Path, dst: pl.Path, *, flags: str = "-arn"
) -> subprocess.CompletedProcess:
    return subprocess.run(["cp", flags, src, dst], check=False)


def CopyAsIs(filename: str, targetdir: pl.Path) -> subprocess.CompletedProcess:
    return Copy(src=Here() / filename, dst=targetdir / filename)


def CopyContents(*, src: pl.Path, dst: pl.Path) -> subprocess.CompletedProcess:
    return subprocess.run(["cp", "-arn", f"{src}/.", f"{dst}/."], check=False)


def Link(src: pl.Path, dst: pl.Path) -> subprocess.CompletedProcess:
    dst.parent.mkdir(parents=True, exist_ok=True)
    return subprocess.run(["ln", "-s", src, dst], check=False)


def LinkRel(src: pl.Path, dst: pl.Path) -> subprocess.CompletedProcess:
    return Link(src=RelativePath(dst, src), dst=dst)


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
    """
                 //-------- From
    --- parent --
                 \\------ To
    To = From -> parent -> To
    """
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

    p = pl.Path()
    for _ in range(count - 1):
        p = p / ".."

    return p / relative


def ListDir(path: pl.Path) -> list[pl.Path]:
    return sorted(path.iterdir() if path.is_dir() else [])


def ListSubDir(path: pl.Path) -> list[pl.Path]:
    return [p for p in ListDir(path) if p.is_dir()]


def ListNames(path: pl.Path) -> list[pl.Path]:
    return [p.name for p in ListDir(path)]


def ListDirRecursive(path: pl.Path) -> list[pl.Path]:
    for p in path.iterdir():
        if p.is_dir():
            yield from ListDirRecursive(p)
        yield p


def CopyHard(src: pl.Path, dst: pl.Path) -> None:
    return Copy(src=src, dst=dst, flags="-rf")


def Match(path: pl.Path, patterns: list[str] | None) -> bool:
    if patterns is None:
        return False
    return any(re.search(pattern, str(path)) for pattern in patterns)


def Update(
    src: pl.Path,
    dst: pl.Path,
    *,
    blacklist: list[str] = None,
    whitelist: list[str] = None,
) -> None:
    dst.mkdir(exist_ok=True, parents=True)
    for next_src in src.iterdir():
        next_dst = dst / next_src.name
        if next_dst.exists():
            in_blacklist = Match(next_dst, blacklist)
            in_whitelist = Match(next_dst, whitelist)
            if in_blacklist and in_whitelist:
                raise ValueError(f"{next_dst} is in blacklist and whitelist")
            if in_blacklist or not in_whitelist:
                continue
        if next_src.is_dir():
            next_dst.mkdir(exist_ok=True, parents=True)
            Update(src=next_src, dst=next_dst,
                   blacklist=blacklist, whitelist=whitelist)
            continue
        CopyHard(src=next_src, dst=next_dst)


def Format(filename: str, check: bool = True) -> str:
    filename = re.sub(" ", "_", filename)
    if check:
        validate_filename(filename)
    return sanitize_filepath(filename)


def Rename(path: pl.Path, target: str):
    shutil.move(path, path.parent / target)


def Delete(path: pl.Path):
    if path.is_file():
        path.unlink()
    if path.is_dir():
        shutil.rmtree(path)


def IsEmptyDir(path: pl.Path):
    return len(ListDir(path)) == 0


BLACKLIST = [
    # r"README.md",
    r".*",
    r"__*",
]
WHITELIST = None


def main() -> None:
    fn = Format(input("Input filename>"), True)
    print(fn)


if __name__ == "__main__":
    main()

import pathlib as pl

from .functions import Copy, CopyAsIs, CopyContents, Link, LinkAsIs


def Export(targetdir: pl.Path) -> None:
    targetdir.mkdir(parents=True, exist_ok=True)
    CopyAsIs("cases", targetdir)
    CopyAsIs("README.md", targetdir)
    LinkAsIs("check.py", targetdir)
    LinkAsIs("main.py", targetdir)
    LinkAsIs("run.py", targetdir)

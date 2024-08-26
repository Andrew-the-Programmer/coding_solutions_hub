import pathlib as pl

import userdir_scratch.export.Export
from export_functions import CopyAsIs

from . import test


def Export(*, problemdir: pl.Path, userdir: pl.Path) -> None:
    problemdir.mkdir(exist_ok=True, parents=True)
    CopyAsIs(problemdir, "README.md")
    userdir_scratch.export.Export(targetdir=userdir)
    test.export.Export(targetdir=problemdir / "test")

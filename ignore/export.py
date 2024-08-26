import pathlib as pl

from .export_functions import CopyContents, Here


def Export(*, problemdir: pl.Path, userdir: pl.Path) -> None:
    pds = Here() / "problemdir_scratch"
    uds = Here() / "userdir_scratch"
    problemdir.mkdir(parents=True, exist_ok=True)
    userdir.mkdir(parents=True, exist_ok=True)
    CopyContents(src=pds, dst=problemdir)
    CopyContents(src=uds, dst=userdir)

import pathlib as pl

import backend.export.Export
import input_output.export.Export

from export_functions import CopyAsIs, LinkAsIs


def Export(targetdir: pl.Path) -> None:
    targetdir.mkdir(parents=True, exist_ok=True)
    CopyAsIs("README.md", targetdir)
    LinkAsIs("main.py", targetdir)
    backend.export.Export(targetdir / "backend")
    input_output.export.Export(targetdir / "input_output")

import pathlib as pl

from export_functions import CopyAsIs, CopyDirsLinkFiles, Here, LinkAsIs


def Export(targetdir: pl.Path) -> None:
    targetdir.mkdir(parents=True, exist_ok=True)
    CopyDirsLinkFiles(src=Here() / "other", dst=targetdir / "other")
    CopyAsIs("solution", targetdir)
    LinkAsIs("CMakeLists.txt", targetdir)
    CopyAsIs("README.md", targetdir)

import pathlib as pl

from export_functions import CopyAsIs, LinkAsIs


def Export(targetdir: pl.Path) -> None:
    targetdir.mkdir(parents=True, exist_ok=True)
    CopyAsIs(".clang-format", targetdir)
    CopyAsIs(".clang-tidy", targetdir)
    LinkAsIs("CMakeLists.txt", targetdir)
    CopyAsIs("README.md", targetdir)
    LinkAsIs("catch.hpp", targetdir)
    LinkAsIs("codestyle_checker.sh", targetdir)
    LinkAsIs("main.py", targetdir)
    LinkAsIs("run-clang-format.py", targetdir)
    CopyAsIs("test_solution.cpp", targetdir)

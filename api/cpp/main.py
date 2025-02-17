import argparse
import pathlib as pl
import subprocess

from my_os import ListNames
from project_navigator import ProjectNavigator, SolutionNavigator

CMAKELISTS = "CMakeLists.txt"


class CppSolutionNavigator(SolutionNavigator):
    def SourceTree(self) -> pl.Path:
        p = self.Path()
        while p != ProjectNavigator.RootDir():
            if CMAKELISTS in ListNames(p):
                return p
            p = p.parent
        return ProjectNavigator.CppDir()

    def OutDir(self) -> pl.Path:
        return self.Hero().Path() / "out"

    def BuildDir(self) -> pl.Path:
        return self.OutDir() / "build"

    def DebugDir(self) -> pl.Path:
        return self.OutDir() / "debug"

    def Executable(self) -> pl.Path:
        return self.BuildDir() / self.Name()

    def CMakeArgs(self) -> list[str]:
        return [
            f"-S {self.SourceTree().absolute()}",
            f"-D SOLUTION_DIR={self.Path().absolute()}",
            f"-D SOLUTION_NAME={self.Name()}",
        ]

    def RunFile(self) -> pl.Path:
        p = self.Hero().Path() / "run.py"
        return p if p.exists() else None

    def BuildWithCMake(self, silent: bool = False):
        build_dir = self.BuildDir()
        build_dir.mkdir(parents=True, exist_ok=True)
        kwargs = {}
        if silent:
            kwargs["stdout"] = subprocess.DEVNULL
            kwargs["stderr"] = subprocess.DEVNULL
        subprocess.run(
            [
                "cmake",
                f"-B {self.BuildDir().absolute()}",
            ]
            + self.CMakeArgs(),
            check=True,
            **kwargs,
        )
        subprocess.run(["make", "-C", build_dir], check=True, **kwargs)

    def Build(self, **kwargs):
        self.BuildWithCMake(**kwargs)

    def RunOnly(self):
        run_file = self.RunFile()
        if run_file is not None:
            return subprocess.run(
                [
                    run_file,
                    self.Path(),
                ],
                check=False,
            )
        # self.Build()
        return subprocess.run(
            [
                self.Executable(),
            ],
            check=False,
        )

    def Run(self):
        self.Build(silent=True)
        return self.RunOnly()


def RunOnly(file: pl.Path):
    solution_dir: pl.Path = file.parent
    sn = CppSolutionNavigator(solution_dir)
    sn.RunOnly()


def Run(file: pl.Path):
    solution_dir: pl.Path = file.parent
    sn = CppSolutionNavigator(solution_dir)
    sn.Run()


def Build(file: pl.Path):
    solution_dir: pl.Path = file.parent
    sn = CppSolutionNavigator(solution_dir)
    sn.Build()


def main() -> None:
    parser = argparse.ArgumentParser(description="Configure and build")
    parser.add_argument("file", type=pl.Path, default=None)
    args = parser.parse_args()
    file: pl.Path = args.file
    # solution_dir = solution_dir.absolute()
    # solution_dir = Here() / "test" / "solution"
    Run(file)


if __name__ == "__main__":
    main()

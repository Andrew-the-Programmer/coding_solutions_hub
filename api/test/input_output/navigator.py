import pathlib as pl
import re
import shutil

from my_os import ListSubDir
from project_navigator import FileNavigator, PathLike

CATEGORY_NAME = "input_output"
INPUT_FILE_NAME = "input.txt"
OUTPUT_FILE_NAME = "output.txt"
CORRECT_OUTPUT_FILE_NAME = "correct_output.txt"


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def IsExecutable(path: pl.Path) -> bool:
    return shutil.which(path) is not None


class RootNavigator(PathLike):
    def TestsDir(self) -> pl.Path:
        return self.Path() / "tests"

    def Tests(self) -> list[pl.Path]:
        return ListSubDir(self.TestsDir())

    def FindChecker(self) -> pl.Path:
        local = self.Path() / "checker.py"
        if local.exists():
            return local
        return Here() / "checkers" / "basic_checker.py"

    def GetUniqueTestName(self) -> str:
        digit_cases = [int(x.name)
                       for x in self.Tests() if re.match(r"[0-9]+", x.name)]
        return str(max(digit_cases) + 1) if digit_cases else "0"

    def GetTest(self, test_name: str | None = None):
        if test_name is None:
            return self.GetTest(self.GetUniqueTestName())
        return TestNavigator(self.TestsDir() / test_name)

    @staticmethod
    def FindRoot(file: pl.Path):
        fn = FileNavigator(file)
        root = fn.Problem().Tests().Path() / CATEGORY_NAME
        return RootNavigator(root)


class TestNavigator(PathLike):
    def InputFile(self) -> pl.Path:
        return self.Path() / INPUT_FILE_NAME

    def OutputFile(self) -> pl.Path:
        return self.Path() / OUTPUT_FILE_NAME

    def CorrectOutputFile(self) -> pl.Path:
        return self.Path() / CORRECT_OUTPUT_FILE_NAME

    def Create(self):
        self.Path().mkdir(parents=True, exist_ok=True)
        self.InputFile().touch()
        self.OutputFile().touch()
        self.CorrectOutputFile().touch()

    def Root(self) -> RootNavigator:
        return RootNavigator(self.Path().parent.parent)

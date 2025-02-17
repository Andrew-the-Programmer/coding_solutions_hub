import pathlib as pl
import re

import attr
from my_os import Here, LinkRel, ListDir, ListSubDir, Update


@attr.define()
class PathLike:
    path: pl.Path | None = attr.field(default=None)

    def Path(self) -> pl.Path:
        return self.path

    def Name(self) -> str:
        return self.path.name


class InputOutputTestsNavigator(PathLike):
    def TestsDir(self) -> pl.Path:
        return self.Path() / "tests"

    def Tests(self) -> list[pl.Path]:
        return ListSubDir(self.TestsDir())

    def TestProgram(self) -> pl.Path:
        return self.path / "test.py"

    def AddTestProgram(self) -> pl.Path:
        return self.path / "add_test.py"


class TestsNavigator(PathLike):
    def Categories(self) -> list:
        return [x.name for x in ListSubDir(self.path)]

    def TestProgram(self) -> pl.Path:
        return self.path / "test.py"

    def AddTestProgram(self) -> pl.Path:
        return self.path / "add_test.py"

    def InputOutput(self) -> InputOutputTestsNavigator:
        return InputOutputTestsNavigator(self.Path() / "input_output")


class SolutionNavigator(PathLike):
    def Hero(self):
        return HeroNavigator(self.path.parent)

    def TestsNavigator(self):
        return self.Hero().Problem().Tests()

    def MainFile(self) -> pl.Path | None:
        for f in ListDir(self.Path()):
            if f.stem == "main":
                return f
        return None


class HeroNavigator(PathLike):
    def Solutions(self) -> list[SolutionNavigator]:
        return [SolutionNavigator(x) for x in ListSubDir(self.path)]

    def Problem(self):
        return ProblemNavigator(self.path.parent)

    def GetSolution(self, hero_name: str = None) -> SolutionNavigator:
        if hero_name is None:
            return self.GetSolution("solution")
        return SolutionNavigator(self.Path() / hero_name)

    def Update(self):
        if self.Name() not in ProjectNavigator.Heroes():
            Update(
                src=ProjectNavigator.HeroScratchDir(),
                dst=ProjectNavigator.HeroesDir() / self.Name(),
            )
        Update(
            src=ProjectNavigator.HeroScratchDir(self.Name()),
            dst=self.path,
        )

    def Create(self):
        self.Update()


class ProblemNavigator(PathLike):
    def Heroes(self) -> list[HeroNavigator]:
        return [HeroNavigator(x) for x in ListSubDir(self.path)]

    def Tests(self) -> TestsNavigator:
        return TestsNavigator(self.path / "test")

    def Id(self) -> int | None:
        m = re.match(r"(\d+)", self.Name())
        if m:
            return int(m[1])
        return None

    def Update(self):
        Update(
            src=ProjectNavigator.ProblemScratchDir(),
            dst=self.path,
        )

    def Create(self):
        self.Update()

    def GetHero(self, hero_name: str) -> HeroNavigator:
        return HeroNavigator(self.path / hero_name)

    def AddHero(self, hero_name: str):
        hero = HeroNavigator(self.path / hero_name)
        hero.Create()

    def GoodSolutionRunner(self) -> SolutionNavigator:
        hn = self.GetHero("good_solution")
        sn = hn.GetSolution("solution")
        mf = sn.MainFile()
        if mf is None or not mf.exists():
            return None
        run = ProjectNavigator.RunExecutable()
        return f"{run} {mf}"


@attr.define()
class ProblemReference(PathLike):
    def Problems(self) -> list[ProblemNavigator]:
        return [ProblemReference(x) for x in ListSubDir(self.path)]

    def Create(self):
        self.Path().mkdir(parents=True, exist_ok=True)

    def AddProblem(self, problem_name: str):
        problem = ProjectNavigator.GetProblem(problem_name)
        problem_path = problem.Path()

        if not problem_path.exists():
            raise ValueError(f"Problem not found: {problem_path}")
        if (self.Path() / problem_name).exists():
            return

        LinkRel(src=problem_path, dst=self.Path() / problem_name)


class ProjectNavigator:
    @staticmethod
    def RootDir() -> pl.Path:
        return Here().parent

    @staticmethod
    def ApiDir() -> pl.Path:
        return ProjectNavigator.RootDir() / "api"

    @staticmethod
    def _Here() -> pl.Path:
        return ProjectNavigator.ApiDir()

    @staticmethod
    def CppDir() -> pl.Path:
        return ProjectNavigator._Here() / "cpp"

    @staticmethod
    def TestDir() -> pl.Path:
        return ProjectNavigator._Here() / "test"

    @staticmethod
    def ProblemsDir() -> pl.Path:
        return ProjectNavigator.RootDir() / "problems"

    @staticmethod
    def CoursesDir() -> pl.Path:
        return ProjectNavigator.RootDir() / "courses"

    @staticmethod
    def _DataDir() -> pl.Path:
        return ProjectNavigator.ApiDir() / "data"

    @staticmethod
    def HeroesDir() -> pl.Path:
        return ProjectNavigator._DataDir() / "heroes"

    @staticmethod
    def HeroScratchDir(name: str | None = None) -> pl.Path:
        if name is None:
            return ProjectNavigator._DataDir() / "hero_scratch"
        p = ProjectNavigator.HeroesDir() / name
        return p if p.exists() else ProjectNavigator.HeroScratchDir()

    @staticmethod
    def ProblemScratchDir() -> pl.Path:
        return ProjectNavigator._DataDir() / "problem_scratch"

    @staticmethod
    def Problems() -> list[ProblemNavigator]:
        for p in ListSubDir(ProjectNavigator.ProblemsDir()):
            yield ProblemNavigator(p)

    @staticmethod
    def GetProblem(name: str) -> ProblemNavigator:
        return ProblemNavigator(ProjectNavigator.ProblemsDir() / name)

    @staticmethod
    def Heroes() -> list[str]:
        return [p.name for p in ListSubDir(ProjectNavigator.HeroesDir())]

    @staticmethod
    def RunExecutable() -> pl.Path:
        return ProjectNavigator.ApiDir() / "run.py"

    @staticmethod
    def TestExecutable() -> pl.Path:
        return ProjectNavigator.ApiDir() / "test.py"

    @staticmethod
    def AddTestExecutable() -> pl.Path:
        return ProjectNavigator.ApiDir() / "add_test.py"

    @staticmethod
    def TestCategories() -> list[str]:
        return [p.name for p in ListSubDir(ProjectNavigator.TestDir())]


class FileNavigator(PathLike):
    def Solution(self) -> SolutionNavigator:
        return SolutionNavigator(self.path.parent)

    def Hero(self) -> HeroNavigator:
        return HeroNavigator(self.Solution().Path().parent)

    def Problem(self) -> ProblemNavigator:
        return ProblemNavigator(self.Hero().Path().parent)

    def Runner(self):
        run = ProjectNavigator.RunExecutable()
        file = self.Path()
        return f"{run} {file}"

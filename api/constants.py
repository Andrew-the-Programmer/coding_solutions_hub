import pathlib as pl


def Here() -> pl.Path:
    return pl.Path(__file__).parent


def FindUserDir(here: pl.Path) -> pl.Path:
    if here == here.parent:
        raise ValueError("No user directory found")
    if "CMakeLists.txt" in [x.name for x in here.iterdir()]:
        return here
    return FindUserDir(here.parent)


USER_DIR = FindUserDir(Here())
OUT_DIR = USER_DIR / "out"
PROBLEM_DIR = USER_DIR.parent
TEST_DIR = PROBLEM_DIR / "test"
TEST_EXECUTABLE = TEST_DIR / "main.py"
ZIP_FILE = USER_DIR / "solution.zip"
ADD_TEST_EXECUTABLE = TEST_DIR / "add_test.py"


def ZipFile(solution_dir: pl.Path) -> pl.Path:
    return USER_DIR / f"{ProjectName(solution_dir)}.zip"


def BuildDir(solution_dir: pl.Path) -> pl.Path:
    return OUT_DIR / "build"


def DebugDir(solution_dir: pl.Path) -> pl.Path:
    return OUT_DIR / "debug"


def ProjectName(solution_dir: pl.Path) -> str:
    return solution_dir.name


def SolutionDir(solution_dir: pl.Path) -> pl.Path:
    return USER_DIR / ProjectName(solution_dir)


def SolutionExecutable(solution_dir: pl.Path) -> pl.Path:
    return BuildDir(solution_dir) / ProjectName(solution_dir)


def DebugExecutable(solution_dir: pl.Path) -> pl.Path:
    return DebugDir(solution_dir) / ProjectName(solution_dir)


def CMakeArgs(solution_dir: pl.Path) -> list[str]:
    project_name = ProjectName(solution_dir)
    return [
        f"-S {USER_DIR}",
        f"-DPROJECT_NAME={project_name}",
        # f"-DPROJECT_SOURCE_DIR={solution_dir}",
    ]

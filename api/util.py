import pathlib


def UserDir(solution_dir: pathlib.Path) -> pathlib.Path:
    return solution_dir.parent


def ProblemDir(solution_dir: pathlib.Path) -> pathlib.Path:
    return UserDir(solution_dir).parent


def CasesDir(solution_dir: pathlib.Path) -> pathlib.Path:
    return ProblemDir(solution_dir) / "test" / "input_output" / "cases"

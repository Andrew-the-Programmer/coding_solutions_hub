#!/bin/python3

import subprocess

from constants import SOLUTION_DIR, SOLUTION_EXECUTABLE, TEST_EXECUTABLE


def Test() -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            TEST_EXECUTABLE,
            "--executable",
            SOLUTION_EXECUTABLE,
            "--solution",
            SOLUTION_DIR,
        ]
    )


# def Test() -> subprocess.CompletedProcess:
#     return subprocess.run(
#         f'{TEST_EXECUTABLE} --executable "{SOLUTION_EXECUTABLE}" --solution "{SOLUTION_DIR}"',
#     )


def main() -> None:
    Test().check_returncode()


if __name__ == "__main__":
    main()

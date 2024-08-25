#!/usr/bin/env python3

import subprocess

from constants import SOLUTION_DIR, SOLUTION_EXECUTABLE, TEST_EXECUTABLE


def Test() -> subprocess.CompletedProcess:
    return subprocess.run(
        [
            TEST_EXECUTABLE,
            f"--executable {SOLUTION_EXECUTABLE}",
            f"--solution {SOLUTION_DIR}",
        ]
    )


def main() -> None:
    Test().check_returncode()


if __name__ == "__main__":
    main()

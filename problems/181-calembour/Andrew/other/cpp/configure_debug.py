#!/usr/bin/env python3

import subprocess

from constants import DEBUG_DIR, USER_DIR


def Configure() -> subprocess.CompletedProcess:
    DEBUG_DIR.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        ["cmake", "-DCMAKE_BUILD_TYPE=Debug", "-S", USER_DIR, "-B", DEBUG_DIR],
        check=True,
    )
    subprocess.run(["make", "-C", DEBUG_DIR], check=True)


def main() -> None:
    Configure().check_returncode()


if __name__ == "__main__":
    main()

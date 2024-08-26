#!/usr/bin/env python3

import subprocess

from constants import BUILD_DIR, USER_DIR

print(USER_DIR)


def Configure() -> subprocess.CompletedProcess:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    return subprocess.run(["cmake", "-S", USER_DIR, "-B", BUILD_DIR])


def main() -> None:
    Configure().check_returncode()


if __name__ == "__main__":
    main()

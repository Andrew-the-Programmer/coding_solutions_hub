#!/usr/bin/env python3

import subprocess

from constants import BUILD_DIR


def Build() -> subprocess.CompletedProcess:
    return subprocess.run(["make", "-C", BUILD_DIR])


def main() -> None:
    Build().check_returncode()


if __name__ == "__main__":
    main()

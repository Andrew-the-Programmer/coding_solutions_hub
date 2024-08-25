#!/usr/bin/env python3

import subprocess

from constants import BUILD_DIR, ROOT_DIR


def Configure() -> subprocess.CompletedProcess:
    BUILD_DIR.mkdir(parents=True, exist_ok=True)
    return subprocess.run(["cmake", "-S", ROOT_DIR, "-B", BUILD_DIR])


def main() -> None:
    Configure().check_returncode()


if __name__ == "__main__":
    main()

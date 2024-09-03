#!/usr/bin/env python3

import subprocess

from constants import DEBUG_DIR, PROJECT_NAME


def Debug() -> subprocess.CompletedProcess:
    return subprocess.run(["gdb", "-tui", DEBUG_DIR / PROJECT_NAME], check=False)


def main() -> None:
    Debug().check_returncode()


if __name__ == "__main__":
    main()

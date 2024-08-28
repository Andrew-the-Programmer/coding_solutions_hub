#!/usr/bin/env python3

import argparse
import pathlib as pl
import subprocess
from typing import Callable, Iterable

import inquirer


def _Select(options: Iterable[str], prompt: str = ">") -> str:
    input_str = "\n".join(options)
    # input_str = "hello world\nbye world"
    process = subprocess.run(
        ["fzf", "--prompt", prompt],
        input=input_str,
        text=True,
        encoding="utf-8",
        stdout=subprocess.PIPE,
    )
    output = process.stdout.split("\n")[0]
    return output


def Select(
    options: list[str],
    *,
    target: str = None,
    prompt: str = None,
    ask_new: bool = True,
    ask_exit: bool = True,
    on_new: Callable = None,
    on_exit: Callable = None,
) -> str:
    new_option_name = "<new>"
    exit_option_name = "<exit>"

    if ask_new:
        options.insert(0, new_option_name)
    if ask_exit:
        options.insert(0, exit_option_name)

    if target is None:
        target = "option"

    if prompt is None:
        prompt = f"Select {target}>"

    if on_exit is None:

        def on_exit():
            return exit(0)

    if on_new is None:

        def on_new():
            return input(f"Input new {target}>")

    selected = _Select(options, prompt=prompt)

    if ask_exit and selected == exit_option_name:
        on_exit()

    if ask_new and selected == new_option_name:
        selected = on_new()
        if not selected or selected in options:
            raise ValueError(f"Invalid new {target}: {selected}")

    return selected


def Confirm(message: str, **kwargs) -> bool:
    yes_option = "yes"
    no_option = "no"
    selected = Select([yes_option, no_option], ask_new=False, prompt=message, **kwargs)
    return selected == yes_option

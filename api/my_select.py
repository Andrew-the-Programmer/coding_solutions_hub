import subprocess
import sys
from typing import Callable, Iterable


def SelectFzf(options: Iterable[str], prompt: str = ">") -> str:
    input_str = "\n".join(options)
    process = subprocess.run(
        ["fzf", "--prompt", prompt],
        input=input_str,
        text=True,
        encoding="utf-8",
        stdout=subprocess.PIPE,
        check=False,
    )
    return process.stdout.split("\n")[0]


def SelectHelper(
    options: list[str],
    *,
    prompt: str,
    actions: dict[str, Callable[[], str] | None] = None,
) -> str:
    options = list(actions.keys()) + options
    selected = SelectFzf(options, prompt=prompt)

    return next(
        (
            action() if action is not None else selected
            for action_name, action in actions.items()
            if selected == action_name
        ),
        selected,
    )


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
    if on_exit is None:

        def on_exit():
            return sys.exit(0)

    if on_new is None:

        def on_new():
            return input(f"Input new {target}>")

    actions = {}
    if ask_new:
        actions["<new>"] = on_new

    if ask_exit:
        actions["<exit>"] = on_exit

    if target is None:
        target = "option"

    if prompt is None:
        prompt = f"Select {target}>"

    return SelectHelper(options, prompt=prompt, actions=actions)


def Confirm(message: str, **kwargs) -> bool:
    yes_option = "yes"
    no_option = "no"
    selected = Select([yes_option, no_option],
                      ask_new=False, prompt=message, **kwargs)
    return selected == yes_option

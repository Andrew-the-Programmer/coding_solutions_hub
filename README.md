# Introduction

Hello :3\
I study in MIPT-FPMI.
This is a collection of all problems I've solved.

# Features

- Here you can find solutions to your problem, possibly. (rn only mine tho 😭)
- You can test your solution here.
- You can contribute your solution, tests and more.
- Find tasks for building, running and testing your solutions.
- Find useful scripts for your needs.

# Project Navigation

## Problems
All problems are in problems/ folder.
They have their own unique id and possibly a description.

## Heroes
Hero is a person who contributed his solution to this project.
Hero folders are in problem's folder.

## Solution
Solution is a folder in hero directory with all files required to run the solution.

> So, the path to solution would be: problems/\<problem>/\<hero>/\<solution>

## Courses
In courses/ folder you can find all problems of your course, linked to problems in problems/ folder.

## Api
There's so much I wouldn't be able to explain. Look at the source code if you want to understand it.

# Usage

## Run

- [run.py](api/run.py)
> Run your solution.
- [run_only.py](api/run_only.py)
> Only run your solution (for c++ programs).
- [build.py](api/build.py)
> Build your solution (for c++ programs).

## Test

- [test.py](api/test.py)
> Test your solution.
- [add_test.py](api/add_test.py)
> Add tests for the problem.

## Other

- [zip_solution.py](api/zip_solution.py)
> Zip your solution.

## Creat

- [creat_problem.py](api/creat_problem.py)
- [creat_hero.py](api/creat_hero.py)

# Tasks

> Tasks are a way to automate certain actions or workflows that you
> frequently perform in your development process.\
> See for more info:
> [vscode-tasks](https://code.visualstudio.com/docs/editor/tasks),
> [neovim-overseer](https://github.com/stevearc/overseer.nvim)

You can find VsCode tasks in [.vscode](.vscode) and
Neovim-Overseer tasks in [nvim/overseer.lua](nvim/overseer.lua).

> Most likely my nvim tasks wont work for you.
> They heavily rely on my nvim config. You can find it
> [here](https://github.com/Andrew-the-Programmer/.dotfiles/tree/main/nvim).
> Probably all vscode tasks also don't work, I used them a while ago.

# Contribute

## Solution

- You'll have to create your own branch for your solution.
  Parent branch can be any.\
  Please name your branch "\<problem>-\<username>", f.e. "175-B-Andrew".

```bash
git switch main
git switch -c <branch-name>
```
- Add your solution. (see [#creat](#Creat))
- Push your branch to origin. Add me as a reviewer.

```bash
git push -u origin <branch-name>
```

- Create a merge request in github/gitlab.
- Wait for it to get merged (or rejected).

## Tests

See [tests folder](api/test).

## Documentation

All documentation can be found in README.md files.
Feel free to modify and extend them. \
Documentation for problems can be found in \<problem>/README.md files. \
Would be really nice if you could add documentation for problems or your solutions 🙏.

# Other notes

[.clang-format](.clang-format) and [.clang-tidy](.clang-tidy) are used
to format your c++ code.\

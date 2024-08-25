# Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Notations](#notations)
- [Usage](#usage)
- [Contribute](#contribute)
    - [Solution](#solution)
    - [Functionality](#functionality)
    - [Tests](#tests)
    - [Documentation](#documentation)
- [Other notes](#other-notes)

# Introduction

Hello :3\
I currently study in MIPT-fpmi.
This is my algorithms homework.

# Features

- Here you can find solutions to your problem, possibly. (rn only mine tho 😭)
- You can test your solution here.
- You can contribute your solution, tests and more.
- Find tasks for building, running and testing your solutions.
- Find useful programs for your needs.

# Notations

For clarity please mind these notations:

- `problemdir = ./<semester>/<contest>/<problem>`\
Directory for the problem.
- `userdir = problemdir/<username>`\
Directory for the user solution.

> It may not make sense rn, but I hope it will eventually, hopefully.

# Usage

## Build, run, test and more!

See [userdir](#notations)/other for useful programs.
They are written by me and can be used by you.
Make sure that they are suitable for your needs.\
 Programs that you can find in [userdir](#notations)/other:

- [configure.py](ignore/solution_scratch/other/configure.py)\
  Build your solution with cmake. See [userdir](#notations)/CMakeLists.txt for more info.
- [build.py](ignore/solution_scratch/other/build.py)\
  Build your solution with make. Executable will be [userdir](#notations)/out/build/Solution.
- [run.py](ignore/solution_scratch/other/run.py)\
  Run your solution.
- [test.py](ignore/solution_scratch/other/test.py)\
  Test your solution. For more info see [problemdir](#notations)/test folder.
- [zip_solution.py](ignore/solution_scratch/other/zip_solution.py)\
  Zip your solution. Find solution.zip file in [userdir](#notations) folder.
- [constants.py](ignore/solution_scratch/other/constants.py) (not executable)\
  Constants for other programs.
  You can modify constants to change functionality a little.

[configure.py](ignore/solution_scratch/other/configure.py),
[build.py](ignore/solution_scratch/other/build.py) and
[run.py](ignore/solution_scratch/other/run.py) are very specific for your needs.
You have to use c++ for them to work.
You could create your own programs for your needs and if you do,
please contribute them to the project.
See [Functionality](#functionality) for more info.\
See [Usage-Tasks](#tasks) to effectively use all this functionality.

## Tasks
>Tasks are a way to automate certain actions or workflows that you
frequently perform in your development process.\
See for more info:
[vscode-tasks](https://code.visualstudio.com/docs/editor/tasks),
[neovim-overseer](https://github.com/stevearc/overseer.nvim)

You can find VsCode tasks in [.vscode](.vscode) and
Neovim-Overseer tasks in [nvim/overseer.lua](nvim/overseer.lua).
>Most likely my nvim tasks wont work for you.
They heavily rely on my nvim config. You can find it
[here](https://github.com/Andrew-the-Programmer/.dotfiles/tree/main/nvim).
Probably all vscode tasks are bad, I used them a while ago.

# Contribute

## Solution

- You'll have to create your own branch for your solution.
  Parent branch can be any.\
  Please name your branch "\<username>-\<problem>", f.e. "Andrew-B".

```bash
git switch main
git switch -c <branch-name>
```

- Run [create_solution.py](create_solution.py) to contribute your solution.
  Process is pretty straight forward.
  You'll be asked to input your username, semester, contest and problem name.
  You can specifythese parameters in the program arguments.
  See ./create_solution.py --help for more info.

```bash
./create_solution.py
```

- Program will create specific folder for your solution.
  It can be found in [userdir](#notations) folder.\
   Put your solution in [userdir](#notations)/solution folder.
- Push your branch to origin. Add me as a reviewer.

```bash
git push -u origin <branch-name>
```

- Create a merge request in github/gitlab.
- Wait for it to get merged (or rejected).

## Tests

You could add your own tests to the database.
Tests can be found in [problemdir](#notations)/test folder.
See [ignore/problem_scratch/test/README.md](ignore/problem_scratch/test/README.md)
for more info.
After that create MR from a new branch.

## Functionality

After running [create_solution.py](create_solution.py) usefull files will be copied to
[problemdir](#notations) and [userdir](#notations) from 
[ignore/problem_scratch](ignore/problem_scratch)
and [ignore/solution_scratch](ignore/solution_scratch).
You can modify them and add something new there if you want.
After that create mr from a new branch.
You could also modify existing [problemdir](#notations) and
[userdir](#notations) (if user don't mind (I don't)).

## Documentation

All documentation can be found in README.md files.
Feel free to modify and extend them.
Documentation for problems can be found in [problemdir](#notations)/README.md files.
Would be really nice if you could add documentation for problems 🙏.

# Other notes

[.clang-format](.clang-format) and [.clang-tidy](.clang-tidy) are used
to format your code.\
In [other](other) you might find useful code.

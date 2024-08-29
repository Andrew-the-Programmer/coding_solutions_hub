# Test your solution on given input and expected output.

## Features
- Test your solution on given input.

## Usage
- Run ./main.py file. See ./main.py --help for more info.
- Use ./main.py Test function. See source code for more info.

## Add new test cases
Add cases in ./cases directory as in the example.

- Create new directory in ./cases. Name it as you like.
- Put input for the solution in input.txt, correct output in correct_output.txt.

When testing std output of your solution will be put in output.txt.

## Add custom checker
By default, the output of your solution will be checked with
`basic_checker.py`, which just gets all words from files and compares them one
by one.
If you need a complex checker, you can set `CHECKER` in contants.py.
>By default `CHECKER = basic_checker.py`.
basic_checker.py stores all words from given files and compares them one by one.

`CHECKER` has to be an executable file which takes two arguments:
--output and --correct-output (see basic_checker.py --help for more info).

You can always see the source code for better understanding.

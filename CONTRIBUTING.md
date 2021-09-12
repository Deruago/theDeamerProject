# Contributing to Deamer Project

 Thanks for taking the time to contribute!

We accept varies forms of contributions, to help you create great contributions we compiled various guidelines to help you contribute. This file will help you with your contributions.

## What should I prepare to start contributing?

### Core projects

It is recommended to always install the core projects. These core projects are used throughout Deamer, and offer various functionalities important in contributing to Deamer Project.

Installing the core projects is as easy as running the [installer.py](https://github.com/Deruago/theDeamerProject/blob/master/installer.py) in the main repo with its default settings.

Core projects:

- [Deamer CC](https://github.com/Deruago/theDeamerProject) ; The infrastructure for compiler and ecosystem generation.
- [Deamer External](https://github.com/Deruago/DeamerExternal) ; The external library for code generated by [Deamer CC](https://github.com/Deruago/theDeamerProject).
- [DLDL](https://github.com/Deruago/DLDL) ; The front-end of Deamer CC and related projects.

### Side projects

There are varies side projects in Deamer projects, one such side project is "[DST](https://github.com/Deruago/DeamerStringTemplate)". If you want to contribute to side projects it is recommended to install that project alongside the core project installation.

## How can I contribute?

### Reporting bugs

No project is perfect even Deamer. Reporting bugs helps us to improve Deamer. It is however important to give proper bug reports, this helps us easier identify problems.

#### I have found a bug?

Before we start writing our report there are a few things we should do:

- Identify what project causes the bug.
- Try finding out which piece of code causes it, and if possible fix the bug.
- Try making a reproduceable example. 
- Check if the bug has been reported before. If it is already reported, add a comment on the existing issue instead of opening a new issue.

#### How to submit a good bug report?

Bugs are tracked as [Github Issues](https://guides.github.com/features/issues/). After you know which project caused your bug, create an issue on that repo and fill in the bug report template.

- **Use a clear and brief descriptive title** for the issue.
- **Give a brief description** of the bug.
- **If needed give a more detailed description** of the bug.
- **State what you expected**, instead of the behaviour the bug caused.
- **Give a piece of code that reproduces the bug**. This helps us to better identify what causes the bug.
- **Additional information**, if you have more useful information you can state this at the end of the report.

### Contributing code

#### Beginners

Unsure how to start contributing to Deamer? There are several tags that help identify **beginner** issues:

- [**beginner issues**](https://github.com/Deruago/theDeamerProject/labels/beginner) ; issues that should only require a few lines of code, and a few tests.

All contributions should be properly tested using google test.

### Testing code

We test our code via google test. To create an unit test suite for a class, mirror the path to the class in the test directory, and create a file with the same name as the class under test. In this new file create the varies unit tests.

### Pull requests

Each new bug fix or contribution gets merged with the development branch using pull requests. Each pull request should properly describe what it adds or fixes. If there are templates available for your scenario use them.

## Style

Before pushing your code to git, make sure to run clang format over the code you have modified. The format for a specific project can be found at its root directory. E.g. [this](https://github.com/Deruago/theDeamerProject/blob/master/Deamer/.clang-format) is the formatting used for Deamer CC.

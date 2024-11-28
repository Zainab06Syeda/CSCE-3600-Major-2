#  Shell Program

## Authors
 -Dylan Throckmorton
 -Snehitha Paruchuri
 -Syeda Zainab
 -Veronica Fuentes

 ## Course Section
 -CSCE 3600.003(8175)

## Description
This is a basic shell program written in C that implements a simple shell with built-in commands and history features.

## Project Organization
- **builtin.c**: It contains implementations for built-in-commands, such as cd, exit, path, and myhistory.
- **history.c**: It is for implementing the myhistory command, which manages the command history.
- **main.c**: It includes the basic shell loop, command parsing, and process handling.
- **Makefile**: It is used for compiling and building the project.
- **README.md**: Provides the documentationof the project.
- **shell.h**: It contains function declarations used across different C files.

## Features
- **cd**: Change the current directory.
- **exit**: Exit the shell.
- **path**: Show the current `PATH` environment variable.
- **myhistory**: View and manage command history.

## Roles and Responsibilities
  Each group member was responsible for one of the the following operations
    - 

## Compilation
To compile the program, run:

```bash
make

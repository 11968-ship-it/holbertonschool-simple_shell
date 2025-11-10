# holbertonschool-simple_shell
This is a simple shell team project to create a simple UNIX shell, written in C, as part of the Holberton School curriculum. It reads and executes commands, supports basic built-ins (`exit`, `env`), and can execute programs in the system PATH


## Holbertonschool-simple_shell
A C project that Features:
1. Interactive shell prompt: `#cisfun$`
2. Handles command execution with arguments
3. Built-in commands:
  - `exit [n]`: exit the shell with status `n` (default: last exit status)
  - `env`: prints the current environment
4. Memory-safe implementation using `malloc` and `free`
5. Basic error handling for command not found


## Usage:

```bash
$ ./hsh
#cisfun$ ls -l
#cisfun$ env
#cisfun$ exit 

```

## Prototypes

```
#ifndef SHELL_H
#define SHELL_H

/* FUNCTION PROTOTYPES */
extern char **environ;
extern int last_exit_status;
void simple_shell(void);
void prompt(void);
void execute(char **argv, const char *shell_name, int *last_exit_status, char *line);
char *read_line(void);
char *find_command_path(const char *command, char **env);

#endif

```


Description
This project implements a simple UNIX command-line shell in C. It reads user input, parses commands,
and executes them as built-ins or by searching the system PATH.
The shell supports basic built-in commands like `exit` and `env`, handles arguments, and manages memory
safely using `malloc` and `free`.

Designed for learning purposes, it reinforces key concepts such as process creation, system calls,
and error handling, giving students practical experience in building a functional shell and understandin
how command execution works in UNIX systems.

Compilation
We used the basic gcc compiler:

```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

Authors
```
Thekira A. Ahmed & Yara K. Alrasheed
```

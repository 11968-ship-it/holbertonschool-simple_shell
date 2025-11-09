#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
* prompt - Prints the shell prompt
* if input is from terminal
*/
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
* read_line - Reads a line from stdin
* and removes the newline
* Return: Pointer to the line
*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread = getline(&line, &len, stdin);

	if (nread == -1)
	{
	free(line);
	return (NULL);
	}

	if (nread > 0 && line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	return (line);
}

/**
* execute - forks and executes
* a single-word command.
* @argv: argument value
* @shell_name: name of this shell (argv[0] of the shell),
* used in errors.
*/
void execute(char **argv, const char *shell_name)
{
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
	perror("fork");
	return;
	}

	if (child_pid == 0)
	{
	execvp(argv[0], argv);
	fprintf(stderr, "%s: 1: %s: not found\n",
	shell_name ? shell_name : "./hsh",
	argv[0] ? argv[0] : "");
	_exit(127);
	}
	else
	{
	wait(NULL);
	}
}

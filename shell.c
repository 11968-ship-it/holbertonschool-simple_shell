#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
* prompt - prints shell prompt
*/
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
* read_line - reads a line and removes newline
* Return: malloc'd string or NULL
*/
char *read_line(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
	free(line);
	return (NULL);
	}

while (nread > 0 && (line[nread - 1] == '\n' ||
line[nread - 1] == ' ' ||
line[nread - 1] == '\r' ||
line[nread - 1] == '\t'))
line[--nread] = '\0';

return (line);
}

/**
* execute - executes a command
* @argv: arguments array
* @shell_name: shell name (for errors)
*/
void execute(char **argv, const char *shell_name, int *last_exit_status)
{
	char *cmd_path;
	pid_t child_pid;
	int status;

	if (!argv || !argv[0])
	return;

	cmd_path = find_command_path(argv[0], environ);
	if (!cmd_path)
	{
	fprintf(stderr, "%s: 1: %s: not found\n",
	shell_name ? shell_name : "./hsh",
	argv[0]);
	*last_exit_status = 127;
	return;
	}

	child_pid = fork();
	if (child_pid == -1)
	{
	perror("fork");
	*last_exit_status = 1;
	free(cmd_path);
	return;
	}

	if (child_pid == 0)
	{
	execv(cmd_path, argv);
	perror("execv");
	_exit(127);
	}
	else
	{
	waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
	*last_exit_status = WEXITSTATUS(status);
	else
	*last_exit_status = 1;
	}
	free(cmd_path);
}

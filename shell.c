#include "shell.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
* prompt - Prints the shell prompt
*/
void prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
* read_line - reads a line and removes newline
*
* Return: A malloc'd string containing the user
* input (without newline), or NULL on EOF or error
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
 * run_child - Forks and executes a command in a child process.
 *
 * Forks the current process to run a command via execv().
 * The parent waits for the child and updates the exit status.
 *
 * @cmd_path: Path to the executable command.
 * @argv: Argument list for the command.
 * @last_exit_status: Pointer to store the command's exit code.
 */
static void run_child(char *cmd_path, char **argv, int *last_exit_status)
{
pid_t child_pid;
	int status;

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
}

/**
 * execute - Runs a command entered by the user.
 *
 * Finds and runs a command by name. Prints an error if not found.
 *
 * @argv: Argument list for the command (argv[0] is the name).
 * @shell_name: Name of the shell, used in error messages.
 * @last_exit_status: Pointer to store the command's exit status.
 */
void execute(char **argv, const char *shell_name, int *last_exit_status)
{
    char *cmd_path;

    if (!argv || !argv[0])
        return;

    if (strcmp(argv[0], "exit") == 0)
    {
     exit(0);
    }

    cmd_path = find_command_path(argv[0], environ);
    if (!cmd_path)
    {
        fprintf(stderr, "%s: 1: %s: not found\n",
                shell_name ? shell_name : "./hsh",
                argv[0]);
        *last_exit_status = 127;
        return;
    }

    run_child(cmd_path, argv, last_exit_status);
    free(cmd_path);
}

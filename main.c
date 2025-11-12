#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
 * build_argv - Split a line into an array of arguments.
 * @line: The input line (will be modified by strtok).
 * @argv_list: The output array of pointers.
 * @max: The maximum number of arguments.
 *
 * Return: The number of tokens parsed (argc).
 */
static int build_argv(char *line, char **argv_list, int max)
{
int i = 0;
char *tok = strtok(line, " \t\n");

while (tok && i + 1 < max)
{
argv_list[i++] = tok;
tok = strtok(NULL, " \t\n");
}
argv_list[i] = NULL;
return (i);
}
/**
 * remove_comment - Remove comments from a command line.
 * @line: The command line (will be modified in place)
 */
void remove_comment(char *line)
{
int i;
if (!line) return;
for (i = 0; line[i]; i++)
{
if (line[i] == '#')
{
if (i == 0 || line[i-1] == ' ' || line[i-1] == '\t')
{
line[i] = '\0';
break;
}
}
}
}
/**
* run_shell - The main read–execute loop of the shell.
* @shell_name: Name of the shell program (argv[0]).
*
* Return: void.
*/
static int run_shell(const char *shell_name)
{
    char *line;
    char *argv_list[64];
    int argcnt;
    int last_exit_status = 0;

    char *line_copy;
    char *command;

    signal(SIGINT, sigint_handler);

    for (;;)
    {
        prompt();
        line = read_line();
        if (!line)
        {
            if (isatty(STDIN_FILENO))
                write(STDOUT_FILENO, "\n", 1);
            break;
        }

        line_copy = strdup(line);
        if (!line_copy)
        {
            free(line);
            continue;
        }

        command = strtok(line_copy, ";");
        while (command)
        {
            while (*command == ' ')
                command++;

remove_comment(command);
            argcnt = build_argv(command, argv_list,
                    (int)(sizeof(argv_list) / sizeof(argv_list[0])));

            if (argcnt > 0)
                execute(argv_list, shell_name, &last_exit_status, line);

            command = strtok(NULL, ";");
        }

        free(line_copy);
        free(line);
        line = NULL;
    }

    return (last_exit_status);
}
/**
 * main - Program entry point.
 * @argc: Argument count.
 * @argv: Argument vector.
 *
 * Description: Initializes the shell name and starts the
 * main shell loop. Handles EOF (Ctrl+D) gracefully.
 *
 * Return: Exit Status.
 */
int main(int argc, char **argv)
{
	const char *shell_name;
	int last_exit_status;

	(void)argc;

	shell_name = (argv && argv[0]) ? argv[0] : "./hsh";
	last_exit_status = run_shell(shell_name);
	return (last_exit_status);
}

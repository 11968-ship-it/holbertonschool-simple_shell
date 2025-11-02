#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* main - Simple shell that runs basic commands.
* Return: Always 0
*/

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
pid_t child_pid;
char *argv[2];

while (1)
{

if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "($) ", 4);
nread = getline(&line, &len, stdin);
if (nread == -1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
break;
}

if (line[nread -1] == '\n')
line[nread - 1] = '\0';

child_pid = fork();
if (child_pid == -1)
{
	perror("Error:");
	continue;
}

if (child_pid == 0)
{
	argv[0] = line;
	argv[1] = NULL;
	if (execve(argv[0], argv, NULL) == -1)
		perror("./hsh");
	exit(EXIT_FAILURE);
}
else
{
	wait(NULL);
}
}
/** write(STDOUT_FILENO, line, nread); */
free(line);
return (0);
}

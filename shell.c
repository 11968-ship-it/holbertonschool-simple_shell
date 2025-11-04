#include <stdlib.h>
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
ssize_t nread;
nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
return (NULL);
}
if (line[nread - 1] == '\n')
line[nread - 1] = '\0';
return (line);
}
/**
* execute - forks and executes
* a single-word command.
* @command: command to execute
*/
void execute(char *command)
{
pid_t child_pid;
char *argv[2];
child_pid = fork();
if (child_pid == -1)
{
perror("fork");
return;
}
if (child_pid == 0)
{
argv[0] = command;
argv[1] = NULL;
if (execve(argv[0], argv, environ) == -1)
fprintf(stderr, "./shell: No such file or directory\n");
exit(EXIT_FAILURE);
}
else
wait(NULL);
}
/**
* main - Simple shell that runs basic commands.
* Return: Always 0
*/
int main(void)
{
char *line;
while (1)
{
prompt();
line = read_line();
if (!line)
{
write(STDOUT_FILENO, "\n", 1);
break;
}
if (line[0] != '\0')
execute(line);
free(line);
}
return (0);
}

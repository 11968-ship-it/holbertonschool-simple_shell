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
* @argv: argument value
*/
void execute(char **argv)
{
pid_t child_pid;

child_pid = fork();

if (child_pid == -1)
{
perror("fork");
return;
}
if (child_pid == 0)
{
if (execve(argv[0], argv, environ) == -1)
{
fprintf(stderr, "./hsh: No such file or directory\n");
}
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
char *line, *token;
char *argv[64];
int i = 0;

while (1)
{
prompt();
line = read_line();
if (!line)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
break;
}

  token = strtok(line, " \t\n");
  while (token != NULL)
    {
      argv[i++] = token;
      token = strtok(NULL, " \t\n");
    }
  argv[i] = NULL;

  if (i > 0)
    execute(argv);
  
free(line);
}
return (0);
}

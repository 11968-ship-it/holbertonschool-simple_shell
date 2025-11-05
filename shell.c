#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

extern char **environ;  // Needed for execve

void prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#cisfun$ ", 9);
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    nread = getline(&line, &len, stdin);
    if (nread == -1)
    {
        free(line);
        return NULL;
    }

    if (line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    return line;
}

void execute(char **argv, char *shell_name)
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
            fprintf(stderr, "%s: No such file or directory\n", shell_name);
            exit(EXIT_FAILURE);
        }
    }
    else
        wait(NULL);
}

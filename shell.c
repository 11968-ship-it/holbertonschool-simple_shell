#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

extern char **environ;

void prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#cisfun$ ", 9);
}

char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread = getline(&line, &len, stdin);

    if (nread == -1)
    {
        free(line);
        return NULL;
    }

    if (nread > 0 && line[nread - 1] == '\n')
        line[nread - 1] = '\0';

    return line;
}

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
        execve(argv[0], argv, environ);
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

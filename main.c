#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

int main(int argc, char **argv)
{
    (void)argc;
    *shell_name = argv[0];
    char *line, *token;
    char *argv_list[64];
    int i;

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

        i = 0;
        token = strtok(line, " \t\n");
        while (token != NULL)
        {
            argv_list[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv_list[i] = NULL;

        if (i > 0)
            execute(argv_list, shell_name);

        free(line);
    }

    return 0;
}

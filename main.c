#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>   /* isatty, write */
#include "shell.h"

int main(int argc, char **argv)
{
    (void)argc;
    const char *shell_name;
    char *line;
    char *token;
    char *argv_list[64];
    int i;

    (void)argc;

    shell_name = (argv && argv[0]) ? argv[0] : "./hsh";
    line = NULL;
    token = NULL;
    
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
        while (token &&
            i + 1 < (int)(sizeof(argv_list) / sizeof(argv_list[0])))
        {
            argv_list[i++] = token;
            token = strtok(NULL, " \t\n");
        }
        argv_list[i] = NULL;

        if (i > 0)
            execute(argv_list, shell_name);

        free(line);
        line = NULL;
    }

    return 0;
}

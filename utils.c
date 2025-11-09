#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
* find_command_path: finds the path of command
* @command: the command name.
*/

char *find_command_path(const char *command)
{
    char *paths[] = { "/bin", "/usr/bin", NULL };
    int i;
    char *fullpath;
    size_t len;
    if (!command)
        return (NULL);
    if (command[0] == '/')
    {
        if (access(command, X_OK) == 0)
        {
            fullpath = malloc(strlen(command) + 1);
            if (!fullpath)
                return (NULL);
            strcpy(fullpath, command);
            return (fullpath);
        }
        return (NULL);
    }
    for (i = 0; paths[i] != NULL; i++)
        {
        len = strlen(paths[i]) + 1 + strlen(command) + 1;
        fullpath = malloc(len);
    if (!fullpath)
        continue;
    strcpy(fullpath, paths[i]);
    strcat(fullpath, "/");
    strcat(fullpath, command);
    if (access(fullpath, X_OK) == 0)
            return (fullpath);
        free(fullpath);
}
    return (NULL);
}

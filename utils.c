#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
 * find_command_path - Finds the full path of a command
 * @command: The command name
 *
 * Return: Allocated string with the full path, or NULL if not found
 */
char *find_command_path(const char *command)
{
    char *path_env, *path_copy, *dir, *fullpath;
    size_t len;

    if (!command)
        return (NULL);

    if (command[0] == '/' || command[0] == '.')
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

    path_env = getenv("PATH");
    if (!path_env)
        path_env = "/bin:/usr/bin";

    path_copy = malloc(strlen(path_env) + 1);
    if (!path_copy)
        return (NULL);
    strcpy(path_copy, path_env);

    dir = strtok(path_copy, ":");
    while (dir)
    {
        len = strlen(dir) + 1 + strlen(command) + 1;
        fullpath = malloc(len);
        if (!fullpath)
        {
            dir = strtok(NULL, ":");
            continue;
        }
        strcpy(fullpath, dir);
        strcat(fullpath, "/");
        strcat(fullpath, command);

        if (access(fullpath, X_OK) == 0)
        {
            free(path_copy);
            return (fullpath);
        }
        free(fullpath);
        dir = strtok(NULL, ":");
    }

    free(path_copy);
    return (NULL);
}

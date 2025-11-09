#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * find_command_path - Finds the full path of a command
 * @command: The command name
 *
 * Return: Pointer to malloc'ed full path, or NULL if not found
 */
char *find_command_path(const char *command)
{
    char *paths[] = { "/bin", "/usr/bin", NULL };
    int i;
    char *fullpath;
    size_t len;

    if (!command)
        return NULL;

    if (command[0] == '/')
    {
        if (access(command, X_OK) == 0)
        {
            fullpath = malloc(strlen(command) + 1);
            if (!fullpath)
                return NULL;
            strcpy(fullpath, command);
            return fullpath;
        }
        return NULL;
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
            return fullpath;
        free(fullpath);
    }

    return NULL;
}

/**
 * get_env_path - Returns the value of the PATH environment variable
 *
 * Return: Pointer to the PATH string, or NULL if not found
 */
char *get_env_path(void)
{
    extern char **environ;
    int i = 0;
    size_t len = strlen("PATH=");

    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", len) == 0)
            return environ[i] + len;
        i++;
    }
    return NULL;
}

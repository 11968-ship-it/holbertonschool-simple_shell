#include "shell.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
 * get_env_path - retrieves the PATH environment variable
 * Return: pointer to PATH string or NULL if not found
 */
char *get_env_path(void)
{
    int i = 0;
    size_t len = strlen("PATH=");
    
    while (environ[i])
    {
        if (strncmp(environ[i], "PATH=", len) == 0)
            return environ[i] + len; // skip "PATH="
        i++;
    }
    return NULL; // PATH not found
}

/**
 * find_command_path - finds the full path of a command using PATH
 * @command: the command to find
 * Return: malloc'ed full path string or NULL if not found
 */
char *find_command_path(const char *command)
{
    char *path_env = get_env_path();
    char *path_copy, *dir, *fullpath;
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

    if (!path_env)
        return NULL;

    path_copy = strdup(path_env); // duplicate PATH string to tokenize
    if (!path_copy)
        return NULL;

    dir = strtok(path_copy, ":");
    while (dir != NULL)
    {
        len = strlen(dir) + 1 + strlen(command) + 1;
        fullpath = malloc(len);
        if (!fullpath)
        {
            free(path_copy);
            return NULL;
        }
        strcpy(fullpath, dir);
        strcat(fullpath, "/");
        strcat(fullpath, command);

        if (access(fullpath, X_OK) == 0)
        {
            free(path_copy);
            return fullpath;
        }

        free(fullpath);
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return NULL;
}

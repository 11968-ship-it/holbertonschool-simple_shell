#include "shell.h"

/**
* find_command_path: finds the path of command
* @cmd: command.
*/

char *find_command_path(const char *cmd)
{
    char *path_env, *path_copy, *dir, full_path[1024];
    if (!cmd)
        return (NULL);
    if (access(cmd, X_OK) == 0)
        return (strdup(cmd)); /* absolute or relative path */
    path_env = getenv("PATH");
    if (!path_env)
        return (NULL);
    path_copy = strdup(path_env);
    dir = strtok(path_copy, ":");
    while (dir)
    {
        snprintf(full_path, sizeof(full_path), "%s/%s", dir, cmd);
        if (access(full_path, X_OK) == 0)
        {
            free(path_copy);
            return (strdup(full_path));
        }
        dir = strtok(NULL, ":");
    }
    free(path_copy);
    return (NULL);
}

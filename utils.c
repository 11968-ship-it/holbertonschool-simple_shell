#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
* get_path_from_env - helper to get PATH from env manually
*
* @env: the environment.
*/
static char *get_path_from_env(char **env)
{
	int i = 0;

	if (!env)
	return (NULL);

	while (env[i])
	{
	if (strncmp(env[i], "PATH=", 5) == 0)
	return env[i] + 5;
	i++;
	}
	return (NULL);
}

/**
* find_command_path - finds full path of a command
* @command: command name
* @env: environment array
*
* Return: malloc'd full path or NULL
*/
char *find_command_path(const char *command, char **env)
{
	char *path_env = get_path_from_env(env);
	char *path_copy, *dir, *fullpath;
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
	return fullpath;
	}
	return (NULL);
	}

	if (!path_env)
	return (NULL);

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

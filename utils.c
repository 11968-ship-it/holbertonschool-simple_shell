#include "shell.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/**
* get_path_from_env - helper to get PATH from env manually
*
* @env: the environment array.
*/
static char *get_path_from_env(char **env)
{
	int i = 0;

	if (!env)
	return (NULL);

	while (env[i])
	{
	if (strncmp(env[i], "PATH=", 5) == 0)
	return (env[i] + 5);
	i++;
	}
	return (NULL);
}

/**
* check_absolute - checks if command is absolute or relative path
*
* @command: command name
*/
static char *check_absolute(const char *command)
{
	char *fullpath;

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
	return (NULL);
}

/**
 * build_fullpath - iterate PATH directories to find command
 * @path_copy: copy of PATH string
 * @command: command string
 * Return: malloc'd full path or NULL
 */
static char *build_fullpath(char *path_copy, const char *command)
{
	char *dir, *fullpath;
	size_t len;

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
	char *path_env, *path_copy, *fullpath;

	if (!command)
	return (NULL);

	fullpath = check_absolute(command);
	if (fullpath)
		return (fullpath);

	path_env = get_path_from_env(env);
	if (!path_env)
		return (NULL);

	path_copy = malloc(strlen(path_env) + 1);
	if (!path_copy)
	return (NULL);
	strcpy(path_copy, path_env);

	fullpath = build_fullpath(path_copy, command);
	free(path_copy);
	
	return (fullpath);
}

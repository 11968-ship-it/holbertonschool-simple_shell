#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
	* _setenv - Initialize or modify an environment variable.
	* @name: variable name (must be non-empty)
	* @value: variable value (may be NULL, treated as "")
	* @overwrite: 1 = overwrite existing, 0 = skip
	* Return: 0 on success, -1 on failure
	*/
int _setenv(const char *name, const char *value, int overwrite)
{
	int idx;

	if (!name || name[0] == '\0')
		return (-1);

	idx = env_find_index(name);
	if (idx >= 0)
	{
		if (!overwrite)
			return (0);
		return (env_replace_index(idx, name, value));
	}
	return (env_append_kv(name, value));
}

/**
	* _unsetenv - Remove an environment variable.
	* @name: variable name
	* Return: 0 on success, -1 on failure
	*
	* Note: Removing a non-existent variable is not an error.
	*/
int _unsetenv(const char *name)
{
	int i, idx;

	if (!name || name[0] == '\0')
		return (-1);

	idx = env_find_index(name);
	if (idx < 0)
		return (0);

	for (i = idx; environ[i]; i++)
		environ[i] = environ[i + 1];

	return (0);
}

/**
	* builtin_env - Display all environment variables.
	*/
void builtin_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
		printf("%s\n", environ[i]);
}

/**
	* handle_setenv_builtin - Wrapper for setenv builtin.
	* @argv: argument vector
	* Return: 0 on success, 1 on failure
	*/
int handle_setenv_builtin(char **argv)
{
if (!argv[1] || !argv[2] || argv[3])
	{
	fprintf(stderr, "Usage: setenv VARIABLE VALUE\n");
	return (1);
	}

	if (_setenv(argv[1], argv[2], 1) == 0)
	return (0);
	return (1);
}

/**
	* handle_unsetenv_builtin - Wrapper for unsetenv builtin.
	* @argv: argument vector
	* Return: 0 on success, 1 on failure
	*/
int handle_unsetenv_builtin(char **argv)
{
	if (!argv[1] || argv[2])
	{
		fprintf(stderr, "Usage: unsetenv VARIABLE\n");
		return (1);
	}

	if (_unsetenv(argv[1]) == 0)
		return (0);

	return (1);
}

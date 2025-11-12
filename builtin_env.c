#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _setenv - Initialize or modify an environment variable.
 * @name: variable name (must be non-empty)
 * @value: variable value (may be NULL, treated as "")
 * @overwrite: 1 = overwrite existing, 0 = skip
 *
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, name_len, count;
	char *new_var, **new_env;
	const char *val = value ? value : "";

	if (!name || name[0] == '\0')
		return (-1);
	name_len = (int)strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, name_len) == 0 &&
		    environ[i][name_len] == '=')
		{
			if (!overwrite)
				return (0);
			new_var = malloc(name_len + strlen(val) + 2);
			if (!new_var)
				return (-1);
			sprintf(new_var, "%s=%s", name, val);
			environ[i] = new_var;
			return (0);
		}
	}

	new_var = malloc(name_len + strlen(val) + 2);
	if (!new_var)
		return (-1);
	sprintf(new_var, "%s=%s", name, val);

	for (count = 0; environ[count]; count++)
		;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
		return (-1);

	for (i = 0; i < count; i++)
		new_env[i] = environ[i];
	new_env[count] = new_var;
	new_env[count + 1] = NULL;
	environ = new_env;
	return (0);
}

/**
 * _unsetenv - Remove an environment variable.
 * @name: variable name
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	int i, j, len;

	if (!name || name[0] == '\0')
		return (-1);

	len = (int)strlen(name);

	for (i = 0; environ[i]; i++)
	{
		if (strncmp(environ[i], name, len) == 0 &&
		    environ[i][len] == '=')
		{
			for (j = i; environ[j]; j++)
				environ[j] = environ[j + 1];
			return (0);
		}
	}
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
 *
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
 *
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

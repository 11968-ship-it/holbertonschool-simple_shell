#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* _setenv - Custom setenv implementation (no realloc on old environ)
* @name: variable name (must be non-empty)
* @value: variable value (may be NULL, treated as "")
* @overwrite: 1 = overwrite existing, 0 = skip
* Return: 0 on success, -1 on failure
*/
int _setenv(const char *name, const char *value, int overwrite)
{
	int i, name_len, count;
	char *new_var, **new_environ;
	const char *val = value ? value : "";

	if (!name || name[0] == '\0')
	return (-1);

	name_len = (int)strlen(name);

	for (i = 0; environ[i]; i++)
	{
	if (strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
	{
	if (!overwrite)
	return (0);

	new_var = malloc(name_len + 1 + strlen(val) + 1);
	if (!new_var)
	return (-1);
	sprintf(new_var, "%s=%s", name, val);
	environ[i] = new_var;
	return (0);
	}
	}

	new_var = malloc(name_len + 1 + strlen(val) + 1);
	if (!new_var)
	return (-1);
	sprintf(new_var, "%s=%s", name, val);

	for (count = 0; environ[count]; count++)
	;

	new_environ = malloc(sizeof(char *) * (count + 2));
	if (!new_environ)
	return (-1);

	for (i = 0; i < count; i++)
	{
	new_environ[i] = environ[i];
	}
	new_environ[count] = new_var;
	new_environ[count + 1] = NULL;

	environ = new_environ;

	return (0);
}

/**
* _unsetenv - Custom unsetenv implementation
* @name: variable name (must be non-empty)
* Return: 0 on success, -1 on failure
*
* Note: Removing a non-existent variable is not an error.
*/
int _unsetenv(const char *name)
{
	int i, j, name_len;

	if (!name || name[0] == '\0')
	return (-1);

	name_len = (int)strlen(name);

	for (i = 0; environ[i]; i++)
	{
	if (strncmp(environ[i], name, name_len) == 0 &&
			environ[i][name_len] == '=')
	{
	for (j = i; environ[j]; j++)
	environ[j] = environ[j + 1];
	return (0);
	}
	}
	return (0);
}

/**
* builtin_env - Display environment variables to stdout
*/
void builtin_env(void)
{
	int i;

	for (i = 0; environ[i]; i++)
	printf("%s\n", environ[i]);
}

/**
* handle_setenv_builtin - setenv wrapper with strict arity
* + stderr usage
* @argv: argument vector
* (expects: setenv VARIABLE VALUE)
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
	else
	return (1);
}

/**
* handle_unsetenv_builtin - unsetenv wrapper with strict arity
* + stderr usage
* @argv: argument vector
* (expects: unsetenv VARIABLE)
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
	else
	return (1);
}

#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * _setenv - Custom setenv implementation (no realloc)
 * @name: variable name
 * @value: variable value (NULL allowed, treated as "")
 * @overwrite: 1 = overwrite existing, 0 = skip
 * Return: 0 on success, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
    int i, name_len, count;
    char *new_var, **new_environ;
    const char *val = value ? value : ""; /* treat NULL as empty string */

    if (!name)
        return (-1);

    name_len = strlen(name);

    /* Check if variable exists */
    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 &&
            environ[i][name_len] == '=')
        {
            if (!overwrite)
                return (0);
            free(environ[i]);
            new_var = malloc(name_len + strlen(val) + 2);
            if (!new_var)
                return (-1);
            sprintf(new_var, "%s=%s", name, val);
            environ[i] = new_var;
            return (0);
        }
    }

    /* Add new variable */
    new_var = malloc(name_len + strlen(val) + 2);
    if (!new_var)
        return (-1);
    sprintf(new_var, "%s=%s", name, val);

    for (count = 0; environ[count]; count++)
        ;

    new_environ = malloc(sizeof(char *) * (count + 2));
    if (!new_environ)
        return (-1);

    for (i = 0; i < count; i++)
        new_environ[i] = environ[i];

    new_environ[count] = new_var;
    new_environ[count + 1] = NULL;
    environ = new_environ;

    return (0);
}

/**
 * _unsetenv - Custom unsetenv implementation
 * @name: variable name
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
    int i, j, name_len;

    if (!name)
        return (-1);

    name_len = strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, name_len) == 0 &&
            environ[i][name_len] == '=')
        {
            free(environ[i]);
            for (j = i; environ[j]; j++)
                environ[j] = environ[j + 1];
            return (0);
        }
    }
    return (0);
}

/**
 * builtin_env - Display environment variables
 */
void builtin_env(void)
{
    int i;

    for (i = 0; environ[i]; i++)
        printf("%s\n", environ[i]);
}

/**
 * handle_setenv_builtin - Wrapper to execute setenv builtin
 * @argv: argument vector
 */
void handle_setenv_builtin(char **argv)
{
    if (!argv[1])
    {
        /* Missing variable name */
        fprintf(stderr, "Usage: setenv VARIABLE [VALUE]\n");
        return;
    }

    if (_setenv(argv[1], argv[2], 1) == 0)
        printf("OK\n");
    else
        fprintf(stderr, "setenv failed\n");
}

/**
 * handle_unsetenv_builtin - Wrapper to execute unsetenv builtin
 * @argv: argument vector
 */
void handle_unsetenv_builtin(char **argv)
{
    if (!argv[1])
    {
        /* Missing variable name */
        fprintf(stderr, "Usage: unsetenv VARIABLE\n");
        return;
}

if (_unsetenv(argv[1]) != 0)
fprintf(stderr, "unsetenv failed\n");
}

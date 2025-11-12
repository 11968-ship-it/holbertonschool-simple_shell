#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

/**
* _setenv - Custom implementation of setenv (no realloc)
* @name: variable name
* @value: variable value
* @overwrite: 1 to overwrite, 0 to skip if exists
* Return: 0 on success, -1 on failure
*/
int _setenv(const char *name, const char *value, int overwrite)
{
int i, name_len, count;
char *new_var, **new_environ;

if (!name || !value)
return (-1);

name_len = strlen(name);

for (i = 0; environ[i]; i++)
{
if (strncmp(environ[i], name, name_len) == 0 &&
environ[i][name_len] == '=')
{
if (!overwrite)
return (0);
new_var = malloc(name_len + strlen(value) + 2);
if (!new_var)
return (-1);
sprintf(new_var, "%s=%s", name, value);
environ[i] = new_var;
return (0);
}
}

new_var = malloc(name_len + strlen(value) + 2);
if (!new_var)
return (-1);
sprintf(new_var, "%s=%s", name, value);

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
* _unsetenv - Custom implementation of unsetenv
* @name: variable name to remove
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
for (j = i; environ[j]; j++)
environ[j] = environ[j + 1];
return (0);
}
}
return (0);
}

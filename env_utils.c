#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * env_find_index - find the index of an env var by name
 * @name: variable name
 * Return: index in environ, or -1 if not found
 */
int env_find_index(const char *name)
{
    int i, nlen;

    if (!name || name[0] == '\0')
        return (-1);

    nlen = (int)strlen(name);

    for (i = 0; environ[i]; i++)
    {
        if (strncmp(environ[i], name, nlen) == 0 && environ[i][nlen] == '=')
            return (i);
    }
    return (-1);
}

/**
 * env_make_kv - allocate "name=value" string
 * @name: variable name
 * @value: variable value (may be NULL)
 * Return: malloc'd "name=value" string, or NULL on failure
 */
char *env_make_kv(const char *name, const char *value)
{
	const char *val = value ? value : "";
    size_t len = strlen(name) + 1 + strlen(val) + 1;
    char *p = malloc(len);

    if (!p)
        return (NULL);

    sprintf(p, "%s=%s", name, val);
    return (p);
}

/**
 * env_replace_index - replace an existing entry in environ (no free)
 * @idx: index to replace
 * @name: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int env_replace_index(int idx, const char *name, const char *value)
{
	char *kv = env_make_kv(name, value);

	if (!kv)
		return (-1);

	free(environ[idx]);
	environ[idx] = kv;
	return (0);
}

/**
 * env_append_kv - append a new "name=value" to environ
 * @name: variable name
 * @value: variable value
 * Return: 0 on success, -1 on failure
 */
int env_append_kv(const char *name, const char *value)
{
	int i, count;
	char **new_env, **old_env; 
	char **new_env, *kv = env_make_kv(name, value);

	if (!kv)
		return (-1);

	for (count = 0; environ[count]; count++)
		;

	new_env = malloc(sizeof(char *) * (count + 2));
	if (!new_env)
	{
		free(kv);
		return (-1);
	}
	
	for (i = 0; i < count; i++)
		new_env[i] = environ[i];

	new_env[count] = kv;
	new_env[count + 1] = NULL;

	old_env = environ;
	environ = new_env;
	free(old_env);
	
	return (0);
}

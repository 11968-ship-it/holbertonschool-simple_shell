#ifndef SHELL_H
#define SHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

/* FUNCTION PROTOTYPES */
extern char **environ;
extern int last_exit_status;
void simple_shell(void);
void prompt(void);
void execute(char **argv, const char *shell_name,
int *last_exit_status, char *line);
char *read_line(void);
char *find_command_path(const char *command, char **env);
void sigint_handler(int sig);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *name);
void builtin_env(void);
int handle_setenv_builtin(char **argv);
int handle_unsetenv_builtin(char **argv);
void remove_comment(char *line);
/* env helper utilities (in env_utils.c) */
int env_find_index(const char *name);
char *env_make_kv(const char *name, const char *value);
int env_replace_index(int idx, const char *name, const char *value);
int env_append_kv(const char *name, const char *value);

#endif

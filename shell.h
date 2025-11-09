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
void execute(char **argv, const char *shell_name);
char *read_line(void);
char *find_command_path(const char *command, char **env);

#endif

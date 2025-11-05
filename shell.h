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

void simple_shell(void);
void prompt(void);
void execute(char **argv, char *shell_name);
char *read_line(void);

#endif

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

#define BUFFER_SIZE 1024

/* FUNCTION PROTOTYPES */
extern char **environ;

void simple_shell(void);
void prompt(void);
void execute(char **argv, *shell_name);
char *read_line(void);

#endif

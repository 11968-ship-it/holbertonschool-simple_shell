#include "shell.h"

/**
* main - Simple shell: promt + read 
* Return: Always 0
*/

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

while (1)
{

if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "($) ", 4);
nread = getline(&line, &len, stdin);
if (nread == -1)
{
if (isatty(STDIN_FILENO))
write(STDOUT_FILENO, "\n", 1);
break;
}
write(STDOUT_FILENO, line, nreade);
}
free(line);
return (0);
}

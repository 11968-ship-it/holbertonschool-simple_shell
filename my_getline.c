#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define READ_SIZE 1024

ssize_t getline(char **lineptr, size_t *n, FILE *stream)
{
static char buffer[READ_SIZE];
static ssize_t buf_pos, buf_size;
ssize_t total = 0;
char *line = NULL;
char c;
if (!lineptr || !n || !stream)
return (-1);
while (1)
{
if (buf_pos >= buf_size)
{
buf_size = read(STDIN_FILENO, buffer, READ_SIZE);
buf_pos = 0;
if (buf_size <= 0)
break;
}
c = buffer[buf_pos++];
line = realloc(line, total + 2);
if (!line)
return (-1);
line[total++] = c;
line[total] = '\0';
if (c == '\n')
break;
}
if (total == 0)
{
free(line);
return (-1);
}
*lineptr = line;
*n = total;
return (total);
}

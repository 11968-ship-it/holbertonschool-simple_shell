#include "shell.h"

/**
* main - Simple shell first step.
* Return: Always 0
*/

int main(void)
{
  if (isatty(STDIN_FILENO))
  write(STDOUT_FILENO, "($) ", 4);

return (0);
}

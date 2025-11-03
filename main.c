#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* print_prompt - Prints the shell prompt
*				if input is from terminal
*/
void print_prompt(void)
{
/* عشان نشيك إذا تم الطباعة فعلياً من الكيبورد (تيرمنال)*/
if (isatty(STDIN_FILENO))
/*استخدمناها بدال برنت اف لأنها system call */
write(STDOUT_FILENO, "#cisfun$ ", 9);
}

/**
* read_line - Reads a line from stdin
*			and removes the newline
* Return: Pointer to the line
*/
char *read_line(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;

nread = getline(&line, &len, stdin);
if (nread == -1)
{
free(line);
return (NULL);
}

	/* إذا ضغطت انتر جيت لاين يخزنه مع إضافة سطر جديد في النهاية وهنا حنا نضيف شرط يزيله*/
if (line[nread - 1] == '\n')
	line[nread -1] = '\0';
/*هنا نحط عملية النسخ نفس قصة أمس*/

	return (line);
}

/**
* execute_command - forks and executes
*					a single-word command.
* @line: command to execute
*/
void execute_command(char *line)
{
	pid_t child_pid;
	char *argv[2];
		/* نبدا في الفورك */
child_pid = fork();
if (child_pid == -1)
{
	perror("Error:");
	return;
}

if (child_pid == 0)
{
	argv[0] = line;
	argv[1] = NULL;
	/*changed NULL to environ*/
	if (execve(argv[0], argv, environ) == -1)
		fprintf(stderr, "%s: No such file or directory\n", line);
	
	exit(EXIT_FAILURE);
}
else
	wait(NULL);
}
	
/**
* main - Simple shell that runs basic commands.
* Return: Always 0
*/
int main(void)
{
	char *line;
	
/*هنا حلقة تدور إلى ما لا نهاية*/
while (1)
{
	print_prompt();

	line = read_line();
	if (!line)
	{
		write(STDOUT_FILENO, "\n", 1);
		break; /*EOF*/
	}

if (line[0] != '\0')  /*يحذف الفراغات*/
    execute_command(line);
	
free(line);
}
return (0);
}

#include "shell.h"
#include <stdlib.h>
#include <stdio.h>

/**
* main - Simple shell that runs basic commands.
* Return: Always 0
*/

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
pid_t child_pid;
char *argv[2];

/*هنا حلقة تدور إلى ما لا نهاية*/
while (1)
{
/* عشان نشيك إذا تم الطباعة فعلياً من الكيبورد (تيرمنال)*/
if (isatty(STDIN_FILENO))
/*استخدمناها بدال برنت اف لأنها system call */
write(STDOUT_FILENO, "#cisfun$ ", 9);

nread = getline(&line, &len, stdin);
if (nread == -1)
{
write(STDOUT_FILENO, "\n", 1);
break; /*EOF*/
}
/* إذا ضغطت انتر جيت لاين يخزنه مع إضافة سطر جديد في النهاية وهنا حنا نضيف شرط يزيله*/
if (line[nread - 1] == '\n')
	line[nread -1] = '\0';
/*هنا نحط عملية النسخ نفس قصة أمس*/

if (line[0] == '\0')  /*يحذف الفراغات*/
    continue; 

	/* نبدا في الفورك */
child_pid = fork();
if (child_pid == -1)
{
	perror("Error:");
	continue;
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
{
	wait(NULL);
}
}
free(line);
return (0);
}

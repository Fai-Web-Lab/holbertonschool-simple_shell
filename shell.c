#include "shell.h"

/**
	* run_shell - Main loop of the shell
	* @simple_shell: Name used to invoke the shell
	*
	* Return: Nothing
	*/
void run_shell(char *simple_shell)
{
	char *lineptr = NULL;
	size_t n = 0;
	ssize_t nread;
	int line_number = 0;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf("($) ");

	nread = getline(&lineptr, &n, stdin);
	if (nread == -1)
	break;

	line_number++;
	if (nread > 1)
	execute_command(lineptr, simple_shell, line_number);
	}

	free(lineptr);
}

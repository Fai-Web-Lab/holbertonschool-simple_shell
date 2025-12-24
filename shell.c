#include "shell.h"

/**
	* run_shell - shell main loop
	* @name: program name
	*
	* Return: void
	*/
void run_shell(char *name)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	printf(":) ");

	read = getline(&line, &len, stdin);
	if (read == -1)
	break;

	if (read > 1)
	execute_command(line, name);
	}
	free(line);
}

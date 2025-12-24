#include "shell.h"

/**
	* main - Entry point for the simple shell
	* Return: 0 on success
	*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	char **args;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, ":) ", 3);

	nread = getline(&line, &len, stdin);
	if (nread == -1)
	{
	free(line);
	exit(0);
	}

	if (line[nread - 1] == '\n')
	line[nread - 1] = '\0';

	args = tokenize(line);
	if (args && args[0])
	execute_command(args);

	free_args(args);
	}
	free(line);
	return (0);
}

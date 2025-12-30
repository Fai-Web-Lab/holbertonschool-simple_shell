#include "shell.h"

/**
	* main - main shell loop
	*
	* Return: 0 on success
	*/
int main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *args[64];
	int i;
	char *token;

	while (1)
	{
	write(STDOUT_FILENO, "$ ", 2);

	read = _getline(&line, &len, STDIN_FILENO);
	if (read == -1)
	break;

	i = 0;
	token = strtok(line, " \t\n");
	while (token && i < 63)
	{
	args[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0])
	execute_command(args[0], args, environ);
	}

	free(line);
	return (0);
}

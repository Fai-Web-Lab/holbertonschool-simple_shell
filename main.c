#include "shell.h"
#include "getline.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
	* main - Entry point for the simple shell
	* @argc: Argument count
	* @argv: Argument vector
	* @env: Environment variables
	*
	* Return: 0 on success
	*/
int main(int argc, char **argv, char **env)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	(void)argc;
	(void)argv;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	print_prompt();

	read = _getline(&line, &len, STDIN_FILENO);
	if (read == -1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "\n", 1);
	break;
	}

	if (read > 1)
	execute_command(line, env);
	}

	free(line);
	return (0);
}

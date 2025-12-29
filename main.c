#include "shell.h"
#include "getline.h"
#include <unistd.h>
#include <stdlib.h>

/**
	* main - Entry point of the shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
	*
	* Return: Always 0
	*/

int main(int ac, char **av, char **env)
{
	char *line = NULL;
	size_t len = 0;
	char **argv;

	(void)ac;
	(void)av;

	while (1)
	{
	write(1, "$ ", 2);

	if (_getline(&line, &len) == -1)
	break;

	argv = split_line(line);

	execute_command(argv, env);

	free_tokens(argv);
	}

	free(line);
	return (0);
}

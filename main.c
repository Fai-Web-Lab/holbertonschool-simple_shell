#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
	* main - entry point of the simple shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
	*
	* Return: always 0
	*
	* Description:
	* - Displays prompt only in interactive mode.
	* - Reads input using getline.
	* - Passes each line to execute_command().
	*/
int main(int ac, char **av, char **env)
{
	shell_ctx_t ctx;
	char *line = NULL;
	size_t len = 0;

	(void)ac;
	(void)av;

	ctx.env = env;
	ctx.last_status = 0;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDERR_FILENO, ":) ", 3);

	if (getline(&line, &len, stdin) == -1)
	break;

	execute_command(&ctx, line);
}

	free(line);
	return (0);
}

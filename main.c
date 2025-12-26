#include <stdlib.h>
#include <unistd.h>
#include "shell.h"
#include "getline.h"

/**
	* main - entry point of the simple shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
	*
	* Description:
	* - Initializes shell context.
	* - Displays prompt in interactive mode.
	* - Reads input using custom getline.
	* - Passes each line to execute_command().
	* - Exits cleanly when exit builtin is triggered.
	*
	* Return: last command status
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
	ctx.should_exit = 0;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, ":) ", 3);

	if (_my_getline(&line, &len) == -1)
	break;

	execute_command(&ctx, line);

	if (ctx.should_exit)
	break;
	}

	free(line);
	return (ctx.last_status);
}

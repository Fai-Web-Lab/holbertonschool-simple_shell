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
	shell_ctx_t ctx;

	(void)ac;
	(void)av;

	ctx.env = env;
	ctx.should_exit = 0;
	ctx.exit_status = 0;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);

	if (_getline(&line, &len) == -1)
	break;

	argv = split_line(line);
if (handle_builtin(&ctx, argv))
	{
	free_tokens(argv);
	if (ctx.should_exit)
	{
	free(line);
	exit(ctx.exit_status);
	}
	continue;
	}

	execute_command(argv, env);

	free_tokens(argv);
	}

	free(line);
	return (0);
}

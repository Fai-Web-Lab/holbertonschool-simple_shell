#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
	* main - Minimal shell for setenv/unsetenv
	* @ac: unused
	* @av: unused
	* @env: environment
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

	ctx.env = copy_env(env);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("$ ");

	if (getline(&line, &len, stdin) == -1)
	break;

	argv = split_line(line);

	if (handle_builtin(&ctx, argv))
	{
	free_tokens(argv);
	continue;
	}

	printf("Command not supported\n");
	free_tokens(argv);
	}

	free(line);
	return (0);
}

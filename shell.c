#include "shell.h"

/**
	* handle_builtin - handles exit and env
	* @argv: arguments
	* @ctx: context
	* Return: 1 if builtin found, 0 if not
	*/
int handle_builtin(char **argv, shell_ctx_t *ctx)
{
	int i;

	if (strcmp(argv[0], "exit") == 0)
	{
	ctx->should_exit = 1;
	return (1);
	}
	if (strcmp(argv[0], "env") == 0)
	{
	i = 0;
	while (ctx->env[i])
	{
	write(STDOUT_FILENO, ctx->env[i], strlen(ctx->env[i]));
	write(STDOUT_FILENO, "\n", 1);
	i++;
	}
	return (1);
	}
	return (0);
}

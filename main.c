#include <stdlib.h>
#include "shell.h"

/**
	* main - entry point of the shell
	* @ac: argument count (unused)
	* @av: argument vector (unused)
	* @env: environment variables
	*
	* Return: always 0
	*/
int main(int ac, char **av, char **env)
{
	shell_ctx_t *ctx = malloc(sizeof(shell_ctx_t));

	(void)ac;
	(void)av;

	if (!ctx)
	return (1);

	ctx->last_status = 0;
	ctx->env = env;

	shell_loop(ctx);
	free_ctx(ctx);

	return (0);
}

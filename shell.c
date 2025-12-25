#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "shell.h"

/**
	* shell_loop - main shell loop
	* @ctx: shell context
	*/
void shell_loop(shell_ctx_t *ctx)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while (1)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, ":) ", 3);

	read = getline(&line, &len, stdin);

	if (read == -1)
	{
	free(line);
	free_ctx(ctx);
	exit(ctx->last_status);
	}

	if (line[0] == '\n')
	continue;

	execute_command(ctx, line);
	}
}
/**
	* free_ctx - free memory allocated in shell context
	* @ctx: shell context
	*/
void free_ctx(shell_ctx_t *ctx)
{
	if (!ctx)
	return;

	free(ctx);
}

#include "shell.h"

/**
	* execute_command - forks and executes
	* @argv: arguments
	* @ctx: context
	*/
void execute_command(char **argv, shell_ctx_t *ctx)
{
	pid_t child;
	int status;
	char *path;

	path = find_path(argv[0], ctx->env);
	if (!path)
	{
	fprintf(stderr, "./shell: %s: not found\n", argv[0]);
	ctx->exit_status = 127;
	return;
	}

	child = fork();
	if (child == 0)
	{
	if (execve(path, argv, ctx->env) == -1)
	{
	perror("execve");
	exit(1);
	}
	}
	else
	{
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	ctx->exit_status = WEXITSTATUS(status);
	}
	free(path);
}

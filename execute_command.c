#include "shell.h"

/**
	* execute_command - forks and executes the command
	* @argv: argument array
	* @ctx: shell context
	*/
void execute_command(char **argv, shell_ctx_t *ctx)
{
	pid_t child;
	int status;
	char *path;

	path = find_path(argv[0], ctx->env);
	if (!path)
	{
	write(STDERR_FILENO, "./hsh: 1: ", 10);
	write(STDERR_FILENO, argv[0], _strlen(argv[0]));
	write(STDERR_FILENO, ": not found\n", 12);
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
	else if (child > 0)
	{
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
	ctx->exit_status = WEXITSTATUS(status);
	}
	else
	perror("fork");
	free(path);
}

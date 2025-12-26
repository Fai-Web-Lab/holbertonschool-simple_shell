#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
	* execute_command - parses and executes a command
	* @ctx: shell context
	* @line: raw input line from getline
	*
	* Description:
	* - Splits line into tokens.
	* - Checks for built-in commands.
	* - Searches PATH for external commands.
	* - Forks and executes using execve().
	*/
void execute_command(shell_ctx_t *ctx, char *line)
{
	char **args = split_line(line);
	pid_t pid;
	int status;
	char *cmd_path;

	if (!args || !args[0])
	{
	free_tokens(args);
	return;
	}

	if (handle_builtin(ctx, args))
	return;

	cmd_path = find_command(args[0], ctx);
	if (!cmd_path)
	{
	fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
	free_tokens(args);
	return;
	}
	pid = fork();
if (pid == 0)
	{
	execve(cmd_path, args, ctx->env);
	perror("simple_shell");
	exit(1);
	}
	else if (pid > 0)
	{
	waitpid(pid, &status, 0);
	ctx->last_status = status;
	}

	free(cmd_path);
	free_tokens(args);
}

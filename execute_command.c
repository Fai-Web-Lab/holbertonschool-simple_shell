#include "shell.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>

/**
	* print_not_found - prints command not found error
	* @cmd: command name
	*/
static void print_not_found(char *cmd)
{
	write(STDERR_FILENO,
	"simple_shell: command not found: ",
	strlen("simple_shell: command not found: "));
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, "\n", 1);
}

/**
	* run_child - executes command in child process
	* @cmd_path: full path to executable
	* @args: argument list
	* @env: environment variables
	*/
static void run_child(char *cmd_path, char **args, char **env)
{
	execve(cmd_path, args, env);
	write(STDERR_FILENO, "simple_shell: ", 14);
	write(STDERR_FILENO, strerror(errno), strlen(strerror(errno)));
	write(STDERR_FILENO, "\n", 1);
	exit(1);
}

/**
	* execute_command - parses and executes a command
	* @ctx: shell context
	* @line: raw input line
	*
	* Description:
	* - Splits line into tokens.
	* - Handles built-ins.
	* - Searches PATH.
	* - Forks and executes external commands.
	*/
void execute_command(shell_ctx_t *ctx, char *line)
{
	char **args = split_line(line);
	char *cmd_path;
	pid_t pid;
	int status;

	if (!args || !args[0])
	{
	(free_tokens(args));
	return;
	}
	if (handle_builtin(ctx, args))
	{
	(free_tokens(args));
	return;
	}
	cmd_path = find_command(args[0], ctx);
	if (!cmd_path)
	{
	print_not_found(args[0]);
	(free_tokens(args));
	return;
	}

	pid = fork();
	if (pid == 0)
	run_child(cmd_path, args, ctx->env);

	waitpid(pid, &status, 0);
	ctx->last_status = status;

	free(cmd_path);
	free_tokens(args);
}

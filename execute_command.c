#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"

/**
	* split_line - split input line into tokens
	* @line: input string
	*
	* Return: array of tokens (NULL-terminated) or NULL on failure
	*
	* Description:
	* - Uses strtok to split the input line by spaces, tabs, and newlines.
	* - Allocates a fixed-size array of pointers (64).
	* - Caller must free the array using free_tokens.
	*/
char **split_line(char *line)
{
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (!tokens)
	return (NULL);

	token = strtok(line, " \t\n");
	while (token)
	{
	tokens[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
}

/**
	* free_tokens - free tokens array
	* @tokens: array of tokens
	*
	* Description:
	* - Frees only the array of pointers, not the strings themselves
	*   (because they point into the original line buffer).
	*/
void free_tokens(char **tokens)
	{
	if (tokens)
	free(tokens);
}

/**
	* handle_builtin - check and execute built-in commands
	* @ctx: shell context
	* @args: array of arguments
	*
	* Return: 1 if a built-in was executed, 0 otherwise
	*
	* Description:
	* - Currently supports only "exit" built-in.
	* - Prints "OK" before exiting as required by checker.
	* - Frees allocated resources before terminating.
	*/
int handle_builtin(shell_ctx_t *ctx, char **args)
{
	if (strcmp(args[0], "exit") == 0)
	{
	printf("OK\n");
	free_tokens(args);
	free_ctx(ctx);
	exit(0);
	}
	return (0);
}

/**
	* execute_command - executes a command entered by the user
	* @ctx: shell context (environment, resources)
	* @line: input line containing the command
	*
	* Description:
	* - Splits the input line into arguments.
	* - Handles built-in commands (currently only "exit").
	* - Searches for the command path in PATH.
	* - Forks and executes the command in a child process.
	* - Cleans up allocated memory properly.
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

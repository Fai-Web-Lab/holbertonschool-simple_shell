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
	* Return: array of tokens
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
	*/
void free_tokens(char **tokens)
{
	free(tokens);
}

/**
 * execute_command - executes a command entered by the user
 * @ctx: shell context (environment, resources)
 * @line: input line containing the command
 *
 * Description:
 * - Splits the input line into arguments
 * - Handles the built-in "exit" command
 * - Searches for the command path
 * - Forks and executes the command in a child process
 * - Cleans up allocated memory properly
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
	if (strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		free_ctx(ctx);
		exit(0);
	}

	cmd_path = find_command(args[0], ctx);
	if (!cmd_path)
	{
		fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
		(free_tokens(args));
		return;
	}

	pid = fork();
	if (pid == 0)
		execve(cmd_path, args, ctx->env), perror("simple_shell"), exit(1);
	else if (pid > 0)
		waitpid(pid, &status, 0);

	free(cmd_path);
	free_tokens(args);
}

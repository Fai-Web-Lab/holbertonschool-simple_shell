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
 * execute_command - execute a command
 * @ctx: shell context
 * @line: input line
*/
void execute_command (shell_ctx_t *ctx, char *line)
{
	char **args;
	pid_t pid = -1;
	int status;
	char *cmd_path;

	(void)ctx;

	args = split_line(line);
	if (args == NULL || args[0] == NULL)
	{
		free_tokens(args);
		return;
	}
	if (strcmp(args[0], "exit") == 0)
	{
		free_tokens(args);
		exit(0);
	}
	cmd_path = find_command(args[0], ctx);
	if (cmd_path == NULL)
	{
		fprintf(stderr, "simple_shell: command not found: %s\n", args[0]);
		free_tokens(args);
		return;
	}
	
	pid = fork();
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("simple_shell");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("fork");
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	free_tokens(args);
}

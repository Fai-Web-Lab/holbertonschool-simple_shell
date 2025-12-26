#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
	* split_line - splits input line into tokens
	* @line: raw input string from getline
	*
	* Return: array of tokens (NULL-terminated)
	*
	* Description:
	* - Uses strtok to split by spaces, tabs, and newlines.
	* - Allocates space for up to 64 tokens.
	* - Caller must free using free_tokens().
	*/
char **split_line(char *line)
{
	char **tokens = malloc(sizeof(char *) * 64);
	char *token;
	int i = 0;

	if (!tokens)
	return (NULL);

	token = strtok(line, " \t\n\r");
	while (token)
	{
	tokens[i++] = token;
	token = strtok(NULL, " \t\n\r");
	}
	tokens[i] = NULL;

	return (tokens);
}

/**
	* free_tokens - frees token array
	* @tokens: array returned by split_line
	*
	* Description:
	* - Only frees the array itself.
	* - Does NOT free the strings because they point inside the original buffer.
	*/
void free_tokens(char **tokens)
{
	if (tokens)
	free(tokens);
}

/**
	* handle_builtin - handles built-in commands like exit
	* @ctx: shell context (stores env + last status)
	* @args: tokenized command
	*
	* Return: 1 if built-in executed, 0 otherwise
	*/
int handle_builtin(shell_ctx_t *ctx, char **args)
{
	if (!args || !args[0])
	return (0);

	if (strcmp(args[0], "exit") == 0)
	{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "OK\n", 3);

	free_tokens(args);
	exit(ctx->last_status);
	}

	return (0);
}

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
	* split_line - splits input line into tokens
	* @line: raw input string
	*
	* Description:
	* - Uses strtok to split by whitespace.
	* - Returns a NULL-terminated array of tokens.
	* - Caller must free using free_tokens().
	*
	* Return: array of tokens or NULL
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
	* - Frees only the array itself.
	* - Does NOT free the strings because they point inside the original buffer.
	*/
void free_tokens(char **tokens)
{
	if (tokens)
	free(tokens);
}

/**
	* handle_builtin - handles built-in commands
	* @ctx: shell context
	* @args: tokenized command
	*
	* Description:
	* - Supports "exit" only.
	* - Returns 1 if built-in executed, 0 otherwise.
	*
	* Return: 1 if handled, 0 otherwise
	*/
int handle_builtin(shell_ctx_t *ctx, char **args)
{
	int status = ctx->exit_status;

	if (!args || !args[0])
	return (0);

	if (strcmp(args[0], "exit") == 0)
	{
	if (args[1])
	status = atoi(args[1]);

	ctx->exit_status = status;
	ctx->should_exit = 1;
	return (1);
	}

	return (0);
}

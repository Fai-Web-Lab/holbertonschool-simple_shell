#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shell.h"

/**
	* copy_token - copy a substring into a new buffer
	* @line: input line
	* @start: start index
	* @len: length of token
	* Return: pointer to new token
	*/
char *copy_token(char *line, int start, int len)
{
	char *token = malloc(len + 1);
	int i;

	if (!token)
	return (NULL);

	for (i = 0; i < len; i++)
	token[i] = line[start + i];

	token[len] = '\0';
	return (token);
}

/**
	* split_line - split input line into tokens
	* @line: input string
	* Return: NULL-terminated array of tokens
	*/
char **split_line(char *line)
{
	int bufsize = 64, i = 0, start = 0, end = 0, len = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);

	if (!tokens)
	return (NULL);

	while (line[end])
	{
	while (line[end] == ' ' || line[end] == '\t' || line[end] == '\n')
	end++;

	start = end;

	while (line[end] &&
	line[end] != ' ' &&
	line[end] != '\t' &&
	line[end] != '\n')
	end++;

	if (start == end)
	break;

	len = end - start;
	tokens[i] = copy_token(line, start, len);
	if (!tokens[i])
	return (NULL);

	i++;

	if (i >= bufsize)
	{
	bufsize *= 2;
	tokens = realloc(tokens, sizeof(char *) * bufsize);
	}
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
	int i = 0;

	if (!tokens)
	return;

	while (tokens[i])
	{
	free(tokens[i]);
	i++;
	}

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
	int status;

	if (!args || !args[0])
	return (0);

	if (strcmp(args[0], "exit") == 0)
	{
	if (args[1])
	status = atoi(args[1]);
	else
	status = ctx->exit_status;

	ctx->exit_status = status;
	ctx->should_exit = 1;
	return (1);
	}

	if (strcmp(args[0], "env") == 0)
	{
	int i = 0;

	while (ctx->env[i])
	{
	write(STDOUT_FILENO, ctx->env[i], strlen(ctx->env[i]));
	write(STDOUT_FILENO, "\n", 1);
	i++;
	}
	return (1);
	}

	return (0);
}

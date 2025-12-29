#include <stdlib.h>
#include <string.h>
#include "shell.h"
#include <stdio.h>
/**
	* split_line - Splits a line into tokens
	* @line: Input string
	*
	* Return: Array of tokens
	*/
char **split_line(char *line)
{
	char **tokens = malloc(64 * sizeof(char *));
	char *token;
	int i = 0;

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
	* free_tokens - Frees token array
	* @tokens: Token array
	*
	* Return: void
	*/
void free_tokens(char **tokens)
{
	free(tokens);
}

/**
	* copy_env - Creates a modifiable copy of the environment
	* @env: Original environment array
	*
	* Return: Pointer to newly allocated environment copy, or NULL on failure
	*/

char **copy_env(char **env)
{
	int i, count = 0;
	char **new_env;

	while (env[count])
	count++;

	new_env = malloc(sizeof(char *) * (count + 1));
	if (!new_env)
	return (NULL);

	for (i = 0; i < count; i++)
	new_env[i] = strdup(env[i]);

	new_env[count] = NULL;
	return (new_env);
}
/**
	* builtin_env - Prints the current environment variables
	* @ctx: Shell context containing the environment array
	*
	* Return: Always 1 (indicates the command was handled)
	*/

int builtin_env(shell_ctx_t *ctx)
{
	int i = 0;

	while (ctx->env[i])
	{
	printf("%s\n", ctx->env[i]);
	i++;
	}
	return (1);
}

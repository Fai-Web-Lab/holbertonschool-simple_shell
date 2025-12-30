#include "shell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/**
	* copy_token - Copies a substring into a new buffer
	* @line: Input line
	* @start: Start index
	* @len: Length of token
	*
	* Return: Pointer to new token or NULL on failure
	*/
char *copy_token(char *line, int start, int len)
{
	char *token;
	int i;

	token = malloc(len + 1);
	if (!token)
	return (NULL);

	for (i = 0; i < len; i++)
	token[i] = line[start + i];

	token[len] = '\0';
	return (token);
}

/**
	* print_prompt - Prints shell prompt
	*
	* Return: void
	*/
void print_prompt(void)
{
	if (isatty(STDIN_FILENO))
	write(STDOUT_FILENO, "$ ", 2);
}

/**
	* print_error - Prints command not found error
	* @cmd: Command name
	*
	* Return: void
	*/
void print_error(char *cmd)
{
	write(STDERR_FILENO, cmd, strlen(cmd));
	write(STDERR_FILENO, ": not found\n", 12);
}

/**
	* copy_env - Creates a modifiable copy of the environment
	* @env: Original environment array
	*
	* Return: Pointer to new environment copy or NULL on failure
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
	* builtin_env - Prints environment variables
	* @ctx: Shell context
	*
	* Return: 1 (command handled)
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

<<<<<<< HEAD
=======
#include <stdlib.h>
#include <string.h>
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
#include "shell.h"
#include <stdio.h>
/**
<<<<<<< HEAD
<<<<<<< HEAD
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
=======
	* print_prompt - prints shell prompt
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
=======
	* split_line - Splits a line into tokens
	* @line: Input string
	*
	* Return: Array of tokens
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
	*/
void print_prompt(void)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int bufsize = 64, i = 0, start = 0, end = 0, len = 0;
	char **tokens = malloc(sizeof(char *) * bufsize);
=======
	char **tokens = malloc(64 * sizeof(char *));
	char *token;
	int i = 0;
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98

	token = strtok(line, " \t\n");
	while (token)
	{
	tokens[i++] = token;
	token = strtok(NULL, " \t\n");
	}
	tokens[i] = NULL;
	return (tokens);
=======
	write(STDOUT_FILENO, "$ ", 2);
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
}

/**
<<<<<<< HEAD
	* print_error - prints command not found error
	* @cmd: command name
=======
	* free_tokens - Frees token array
	* @tokens: Token array
	*
	* Return: void
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
	*/
void print_error(char *cmd)
{
<<<<<<< HEAD
<<<<<<< HEAD
	int i = 0;

	if (!tokens)
	return;

	while (tokens[i])
	{
	free(tokens[i]);
	i++;
	}

=======
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
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
<<<<<<< HEAD
	}
	return (0);
=======
	write(STDERR_FILENO, cmd, 0);
	write(STDERR_FILENO, ": not found\n", 12);
>>>>>>> 6c97ab6 (working on advanced 9: simple shell 0.1.1)
=======
>>>>>>> 0de24339ba50e0f0950489c943d8157701d34a98
}

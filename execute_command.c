#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


/**
	* find_env_index - Finds index of an environment variable
	* @env: Environment array
	* @name: Variable name
	*
	* Return: index or -1 if not found
	*/
int find_env_index(char **env, char *name)
{
	int i, len = strlen(name);

	for (i = 0; env[i]; i++)
	if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
	return (i);

	return (-1);
}

/**
	* build_env_var - Builds NAME=VALUE string
	* @name: Variable name
	* @value: Variable value
	*
	* Return: Newly allocated string or NULL
	*/
char *build_env_var(char *name, char *value)
{
	int len = strlen(name) + strlen(value) + 2;
	char *var = malloc(len);

	if (!var)
	return (NULL);

	strcpy(var, name);
	strcat(var, "=");
	strcat(var, value);

	return (var);
}

/**
	* builtin_setenv - Implements the setenv builtin command
	* @ctx: Shell context
	* @args: Command arguments
	*
	* Return: Always 1
	*/
int builtin_setenv(shell_ctx_t *ctx, char **args)
{
	int idx;
	char *new_var;

	if (!args[1] || !args[2])
	{
	write(STDERR_FILENO, "setenv: Invalid arguments\n", 26);
	return (1);
	}

	new_var = build_env_var(args[1], args[2]);
	if (!new_var)
	{
	write(STDERR_FILENO, "setenv: malloc failed\n", 22);
	return (1);
	}

	idx = find_env_index(ctx->env, args[1]);

	if (idx >= 0)
	ctx->env[idx] = new_var;
	else
	{
	int i;

	for (i = 0; ctx->env[i]; i++)
	;
	ctx->env[i] = new_var;
	ctx->env[i + 1] = NULL;
	}

	return (1);
}

/**
	* builtin_unsetenv - Implements the unsetenv builtin command
	* @ctx: Shell context
	* @args: Command arguments
	*
	* Return: Always 1
	*/
int builtin_unsetenv(shell_ctx_t *ctx, char **args)
{
	int i, j, len;

	if (!args[1])
	{
	write(STDERR_FILENO, "unsetenv: Invalid arguments\n", 28);
	return (1);
	}

	len = strlen(args[1]);

	for (i = 0; ctx->env[i]; i++)
	{
	if (strncmp(ctx->env[i], args[1], len) == 0 && ctx->env[i][len] == '=')
	{
	for (j = i; ctx->env[j]; j++)
	ctx->env[j] = ctx->env[j + 1];
	return (1);
	}
	}

	return (1);
}

/**
	* handle_builtin - Checks and executes builtin commands
	* @ctx: Shell context
	* @args: Parsed command arguments
	*
	* Return: 1 if builtin executed, 0 otherwise
	*/
int handle_builtin(shell_ctx_t *ctx, char **args)
{
	if (!args || !args[0])
	return (0);

	if (strcmp(args[0], "setenv") == 0)
	return (builtin_setenv(ctx, args));

	if (strcmp(args[0], "unsetenv") == 0)
	return (builtin_unsetenv(ctx, args));

	if (strcmp(args[0], "printenv") == 0)
	{
	int i;

	for (i = 0; ctx->env[i]; i++)
	printf("%s\n", ctx->env[i]);
	return (1);
}
	return (0);
}

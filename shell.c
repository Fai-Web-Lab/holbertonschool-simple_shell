#include "shell.h"

/**
	* handle_builtin - checks if command is a builtin and executes it
	* @argv: argument vector
	* @ctx: shell context structure
	*
	* Return: 1 if command was a builtin, 0 otherwise
	*/
int handle_builtin(char **argv, shell_ctx_t *ctx)
{
	if (_strcmp(argv[0], "exit") == 0)
	{
	ctx->should_exit = 1;
	return (1);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
	int i;

	for (i = 0; ctx->env[i]; i++)
	{
	write(STDOUT_FILENO, ctx->env[i], _strlen(ctx->env[i]));
	write(STDOUT_FILENO, "\n", 1);
	}
	ctx->exit_status = 0;
	return (1);
	}
	if (_strcmp(argv[0], "setenv") == 0)
	{
	_setenv(argv, ctx);
	return (1);
	}
	if (_strcmp(argv[0], "unsetenv") == 0)
	{
	_unsetenv(argv, ctx);
	return (1);
	}
	return (0);
}

/**
	* _setenv - adds or modifies an environment variable
	* @argv: arguments (setenv VARIABLE VALUE)
	* @ctx: shell context
	*
	* Return: 0 on success
	*/
int _setenv(char **argv, shell_ctx_t *ctx)
{
	int i, j, len;
	char *new_var;

	if (!argv[1] || !argv[2])
	{
	ctx->exit_status = 0;
	return (0);
	}
	len = _strlen(argv[1]) + _strlen(argv[2]) + 2;
	new_var = malloc(len);
	if (!new_var)
	return (0);
	for (i = 0; argv[1][i]; i++)
	new_var[i] = argv[1][i];
	new_var[i++] = '=';
	for (j = 0; argv[2][j]; j++)
	new_var[i + j] = argv[2][j];
	new_var[i + j] = '\0';
	for (i = 0; ctx->env[i]; i++)
	{
	if (_strncmp(ctx->env[i], argv[1], _strlen(argv[1])) == 0 &&
	ctx->env[i][_strlen(argv[1])] == '=')
	{
	ctx->env[i] = new_var;
	ctx->exit_status = 0;
	return (0);
	}
	}
	ctx->env[i] = new_var;
	ctx->env[i + 1] = NULL;
	ctx->exit_status = 0;
	return (0);
}

/**
	* _unsetenv - removes an environment variable
	* @argv: arguments (unsetenv VARIABLE)
	* @ctx: shell context
	*
	* Return: 0 on success
	*/
int _unsetenv(char **argv, shell_ctx_t *ctx)
{
	int i, j, len;

	if (!argv[1])
	{
	ctx->exit_status = 0;
	return (0);
	}
	len = _strlen(argv[1]);
	for (i = 0; ctx->env[i]; i++)
	{
	if (_strncmp(ctx->env[i], argv[1], len) == 0 &&
	ctx->env[i][len] == '=')
	{
	for (j = i; ctx->env[j]; j++)
	ctx->env[j] = ctx->env[j + 1];
	ctx->exit_status = 0;
	return (0);
	}
	}
	ctx->exit_status = 0;
	return (0);
}

#include "shell.h"

/**
	* _getenv - gets the value of an environment variable
	* @name: variable name
	* @env: environment array
	* Return: value string or NULL
	*/
char *_getenv(char *name, char **env)
{
	int i, len = _strlen(name);

	for (i = 0; env[i]; i++)
	{
	if (_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
	return (env[i] + len + 1);
	}
	return (NULL);
}

/**
	* _cd - changes the current working directory
	* @argv: arguments
	* @ctx: shell context
	* Return: 0 on success, 1 on failure
	*/
int _cd(char **argv, shell_ctx_t *ctx)
{
	char *path, *old_pwd, pwd_buf[BUF_SIZE];
	char *home = _getenv("HOME", ctx->env);
	char *prev = _getenv("OLDPWD", ctx->env);
	char *setenv_args[4];

	old_pwd = getcwd(pwd_buf, BUF_SIZE);
	if (!argv[1] || _strcmp(argv[1], "$HOME") == 0)
	path = home ? home : old_pwd;
	else if (_strcmp(argv[1], "-") == 0)
	{
	path = prev ? prev : old_pwd;
	write(STDOUT_FILENO, path, _strlen(path));
	write(STDOUT_FILENO, "\n", 1);
	}
	else
	path = argv[1];

	if (chdir(path) != 0)
	{
	perror("cd");
	return (1);
	}
	setenv_args[0] = "setenv";
	setenv_args[1] = "OLDPWD";
	setenv_args[2] = old_pwd;
	setenv_args[3] = NULL;
	_setenv(setenv_args, ctx);
	getcwd(pwd_buf, BUF_SIZE);
	setenv_args[1] = "PWD";
	setenv_args[2] = pwd_buf;
	_setenv(setenv_args, ctx);
	return (0);
}

/**
	* _setenv - adds or modifies an environment variable
	* @argv: arguments
	* @ctx: shell context
	* Return: 0
	*/
int _setenv(char **argv, shell_ctx_t *ctx)
{
	int i, j, len;
	char *new_var;

	if (!argv[1] || !argv[2])
	return (0);
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
	free(ctx->env[i]);
	ctx->env[i] = new_var;
	return (0);
	}
	}
	ctx->env[i] = new_var;
	ctx->env[i + 1] = NULL;
	return (0);
}

/**
	* handle_builtin - dispatches built-in commands
	* @argv: arguments
	* @ctx: context
	* Return: 1 if handled
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
	if (_strcmp(argv[0], "cd") == 0)
	return (_cd(argv, ctx) || 1);
	if (_strcmp(argv[0], "setenv") == 0)
	return (_setenv(argv, ctx) || 1);
	if (_strcmp(argv[0], "unsetenv") == 0)
	return (_unsetenv(argv, ctx) || 1);
	return (0);
}

#include "shell.h"

/**
	* _strcmp - compares two strings
	* @s1: first string
	* @s2: second string
	* Return: difference between strings
	*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
	s1++;
	s2++;
	}
	return (*s1 - *s2);
}

/**
	* print_cd_error - prints custom error message for cd failures
	* @path: the path that failed
	* @ctx: shell context
	*/
void print_cd_error(char *path, shell_ctx_t *ctx)
{
	char *err = "./hsh: 1: cd: can't cd to ";

	write(STDERR_FILENO, err, _strlen(err));
	write(STDERR_FILENO, path, _strlen(path));
	write(STDERR_FILENO, "\n", 1);
	ctx->exit_status = 2;
}

/**
	* _cd - changes directory
	* @argv: arguments
	* @ctx: context
	* Return: 0 or 1
	*/
int _cd(char **argv, shell_ctx_t *ctx)
{
	char *path, *old_pwd, pwd_buf[BUF_SIZE];
	char *home = _getenv("HOME", ctx->env);
	char *prev = _getenv("OLDPWD", ctx->env);
	char *s_args[4];

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
	print_cd_error(path, ctx);
	return (1);
	}
	s_args[0] = "setenv";
	s_args[1] = "OLDPWD";
	s_args[2] = old_pwd;
	s_args[3] = NULL;
	_setenv(s_args, ctx);
	getcwd(pwd_buf, BUF_SIZE);
	s_args[1] = "PWD";
	s_args[2] = pwd_buf;
	_setenv(s_args, ctx);
	ctx->exit_status = 0;
	return (0);
}

/**
	* _setenv - set environment variable
	* @argv: arguments
	* @ctx: context
	* Return: 0
	*/
int _setenv(char **argv, shell_ctx_t *ctx)
{
	int i, j, len;
	char *nv;

	if (!argv[1] || !argv[2])
	return (0);

	len = _strlen(argv[1]) + _strlen(argv[2]) + 2;
	nv = malloc(len);
	if (!nv)
	return (0);

	for (i = 0; argv[1][i]; i++)
	nv[i] = argv[1][i];
	nv[i++] = '=';
	for (j = 0; argv[2][j]; j++)
	nv[i + j] = argv[2][j];
	nv[i + j] = '\0';

	for (i = 0; ctx->env[i]; i++)
	{
	if (_strncmp(ctx->env[i], argv[1], _strlen(argv[1])) == 0 &&
	ctx->env[i][_strlen(argv[1])] == '=')
	{
	free(ctx->env[i]);
	ctx->env[i] = nv;
	return (0);
	}
	}
	ctx->env[i] = nv;
	ctx->env[i + 1] = NULL;
	return (0);
}

/**
	* handle_builtin - handle builtin commands
	* @argv: arguments
	* @ctx: context
	* Return: 1 or 0
	*/
int handle_builtin(char **argv, shell_ctx_t *ctx)
{
	int i;

	if (_strcmp(argv[0], "exit") == 0)
	{
	ctx->should_exit = 1;
	return (1);
	}
	if (_strcmp(argv[0], "env") == 0)
	{
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

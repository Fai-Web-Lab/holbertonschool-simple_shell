#include "shell.h"

/**
	* _getenv - gets the value of an environment variable
	* @name: variable name
	* @env: environment array
	* Return: pointer to value or NULL
	*/
char *_getenv(char *name, char **env)
{
	int i, len;

	if (name == NULL || env == NULL)
	return (NULL);
	len = _strlen(name);
	for (i = 0; env[i]; i++)
	{
	if (_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
	return (env[i] + len + 1);
	}
	return (NULL);
}

/**
	* _strncmp - compares n characters of two strings
	* @s1: string 1
	* @s2: string 2
	* @n: limit
	* Return: diff
	*/
int _strncmp(char *s1, char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n && s1[i] && s2[i]; i++)
	{
	if (s1[i] != s2[i])
	return (s1[i] - s2[i]);
	}
	if (i == n)
	return (0);
	return (s1[i] - s2[i]);
}

/**
	* is_delim - checks delimiter
	* @c: char
	* @delim: delims
	* Return: 1 or 0
	*/
int is_delim(char c, const char *delim)
{
	while (*delim)
	{
	if (c == *delim)
	return (1);
	delim++;
	}
	return (0);
}

/**
	* _strtok - custom tokenizer
	* @str: string
	* @delim: delims
	* Return: token
	*/
char *_strtok(char *str, const char *delim)
{
	static char *last;
	char *token;

	if (str != NULL)
	last = str;
	if (last == NULL || *last == '\0')
	return (NULL);
	while (*last && is_delim(*last, delim))
	last++;
	if (*last == '\0')
	return (NULL);
	token = last;
	while (*last && !is_delim(*last, delim))
	last++;
	if (*last != '\0')
	{
	*last = '\0';
	last++;
	}
	return (token);
}

/**
	* _unsetenv - removes env var
	* @argv: args
	* @ctx: context
	* Return: 0
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
	free(ctx->env[i]);
	for (j = i; ctx->env[j]; j++)
	ctx->env[j] = ctx->env[j + 1];
	ctx->exit_status = 0;
	return (0);
	}
	}
	ctx->exit_status = 0;
	return (0);
}

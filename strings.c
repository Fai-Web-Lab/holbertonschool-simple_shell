#include "shell.h"

/**
	* _strcmp - compares two strings
	* @s1: first string
	* @s2: second string
	*
	* Return: 0 if equal, otherwise the difference between chars
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
	* is_delim - checks if a character is a delimiter
	* @c: char to check
	* @delim: delimiter string
	*
	* Return: 1 if it is a delimiter, 0 otherwise
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
	* _strtok - custom string tokenizer that maintains state with a static pointer
	* @str: string to tokenize
	* @delim: delimiter string
	*
	* Return: pointer to the next token, or NULL
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
	* copy_env - creates a heap-allocated copy of the system environment
	*
	* Return: pointer to the new environment array
	*/
char **copy_env(void)
{
	int i, count = 0;
	char **new_env;

	while (environ[count])
	count++;

	new_env = malloc(sizeof(char *) * (count + 64));
	if (!new_env)
	return (NULL);

	for (i = 0; i < count; i++)
	new_env[i] = _strdup(environ[i]);
	new_env[i] = NULL;

	return (new_env);
}

/**
	* _unsetenv - removes an environment variable from the shell context
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

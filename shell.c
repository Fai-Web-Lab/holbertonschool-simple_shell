#include "shell.h"

/**
	* _strcmp - compares two strings
	* @s1: first string
	* @s2: second string
	*
	* Return: difference
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
	* is_delim - checks if char is a delimiter
	* @c: char to check
	* @delim: delimiter string
	*
	* Return: 1 if true, 0 if false
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
	* _strtok - custom string tokenizer
	* @str: string to tokenize
	* @delim: delimiter string
	*
	* Return: pointer to next token
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
	* handle_builtin - executes built-in commands
	* @argv: arguments
	* @ctx: shell context
	*
	* Return: 1 if handled, 0 otherwise
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
	return (1);
	}
	return (0);
}

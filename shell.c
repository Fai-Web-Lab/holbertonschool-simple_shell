#include "shell.h"

/**
	* _realloc - reallocates a memory block using malloc and free
	* @ptr: pointer to the memory previously allocated
	* @old_size: size in bytes of the allocated space for ptr
	* @new_size: size in bytes of the new memory block
	* Return: pointer to the new memory block
	*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr, *old_ptr = ptr;
	unsigned int i;

	if (new_size == old_size)
	return (ptr);
	if (new_size == 0 && ptr != NULL)
	{
	free(ptr);
	return (NULL);
	}
	if (ptr == NULL)
	return (malloc(new_size));

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
	new_ptr[i] = old_ptr[i];

	free(ptr);
	return (new_ptr);
}

/**
	* _strtok - custom string tokenizer
	* @str: string to tokenize
	* @delim: delimiter string
	* Return: pointer to next token or NULL
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
	* handle_builtin - checks and executes exit or env
	* @argv: arguments
	* @ctx: shell context
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

/**
	* _strcmp - compares two strings
	* @s1: string 1
	* @s2: string 2
	* Return: 0 if equal
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
